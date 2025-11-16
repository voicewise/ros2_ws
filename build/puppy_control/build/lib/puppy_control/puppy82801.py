#!/usr/bin/python3
# coding=utf8
# Author: Summer
# Email: 997950600@qq.com

import time
import os, sys, math
import numpy as np
import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt8, UInt16, Float32, Float64, Bool, String, Float32MultiArray
from std_srvs.srv import Empty, SetBool
from ros_robot_controller_msgs.msg import BuzzerState
from geometry_msgs.msg import Point32, Polygon, Twist
from puppy_control_msgs.srv import SetRunActionName
from sensor_msgs.msg import Imu, JointState
from rclpy.duration import Duration
from std_msgs.msg import Float64
from puppy_control_msgs.msg import Velocity, Gait, SetServo, Pose
from puppy_control_msgs.srv import SetInt64

sys.path.append('/home/ubuntu/software/puppypi_control')
from servo_controller import setServoPulse, updatePulse
from action_group_control import runActionGroup, stopActionGroup
from puppy_kinematics import HiwonderPuppy, PWMServoParams

with_arm = 0
if with_arm:
    offset = 0.1
else:
    offset = 0

# Define Pose configurations
Stand = {'roll': math.radians(0), 'pitch': math.radians(0), 'yaw': 0.0, 'height': -10, 'x_shift': -0.5 + offset, 'stance_x': 0, 'stance_y': 0}
LieDown = {'roll': 0.0, 'pitch': 0.0, 'yaw': 0.0, 'height': -5, 'x_shift': 2, 'stance_x': 0, 'stance_y': 0}
LookDown = {'roll': math.radians(0), 'pitch': math.radians(-15), 'yaw': 0.0, 'height': -10, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0}
StandLow = {'roll': math.radians(0), 'pitch': math.radians(0), 'yaw': 0.0, 'height': -7, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0}
PuppyPose = LieDown.copy()

# Gait configurations
GaitConfigFast = {'overlap_time': 0.1, 'swing_time': 0.15, 'clearance_time': 0.0, 'z_clearance': 5}
GaitConfigSlow = {'overlap_time': 0.4, 'swing_time': 0.3, 'clearance_time': 0.26, 'z_clearance': 4}
GaitConfigMarkTime = {'overlap_time': 0.2, 'swing_time': 0.1, 'clearance_time': 0.0, 'z_clearance': 5}
GaitConfig = GaitConfigFast.copy()

# MPU6050 class for IMU data processing
class MPU6050(Node):

    def __init__(self):
        super().__init__('mpu6050')
        self.subscription = self.create_subscription(Imu, '/ros_robot_controller/imu_raw', self.get_imu_fun, 10)
        self.data = {'accel': [0, 0, 0], 'gyro': [0, 0, 0]}
        self.second_order_filter_x = self._second_order_filter()
        self.second_order_filter_y = self._second_order_filter()

    def get_imu_fun(self, msg):
        self.data['accel'][0] = msg.linear_acceleration.x
        self.data['accel'][1] = msg.linear_acceleration.y
        self.data['accel'][2] = msg.linear_acceleration.z
        self.data['gyro'][0] = msg.angular_velocity.x
        self.data['gyro'][1] = msg.angular_velocity.y
        self.data['gyro'][2] = msg.angular_velocity.z

    def _second_order_filter(self):
        x1, x2, y1, angle = 0, 0, 0, 0
        K2 = 0.02

        def fun(angle_m, gyro_m, dt=0.01):
            nonlocal x1, x2, y1, angle, K2
            x1 = (angle_m - angle) * (1 - K2) * (1 - K2)
            y1 = y1 + x1 * dt
            x2 = y1 + 2 * (1 - K2) * (angle_m - angle) + gyro_m
            angle = angle + x2 * dt
            return angle

        return fun

    def get_euler_angle(self, dt=0.01):
        accel_Y = math.atan2(self.data['accel'][0], self.data['accel'][2]) * 180 / math.pi
        gyro_Y = self.data['gyro'][1]
        angleY = self.second_order_filter_y(-accel_Y, gyro_Y, dt)

        accel_X = math.atan2(self.data['accel'][1], self.data['accel'][2]) * 180 / math.pi
        gyro_X = self.data['gyro'][0]
        angleX = self.second_order_filter_x(accel_X, gyro_X, dt)

        return {'pitch': -math.radians(angleX), 'roll': -math.radians(angleY), 'yaw': 0}


# PUPPY class for controlling the robot
class PUPPY(Node):

    def __init__(self):
        super().__init__('puppy_control')
        self.declare_parameters(
            namespace='',
            parameters=[
                ('joint_state_pub_topic', 'false'),
                ('joint_state_controller_pub_topic', 'false')
            ]
        )

        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').get_parameter_value().string_value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').get_parameter_value().string_value

        self.puppy = HiwonderPuppy(setServoPulse=setServoPulse, servoParams=PWMServoParams(), dof='8')
        self.mpu = MPU6050()
        self.puppy.imu = None  # 

        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'], clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])

        self.puppy.start()
        self.puppy.move_stop(servo_run_time=500)

        # ROS 2 Service and Subscription Initialization
        self.create_service(SetBool, '/%s/set_running' % self.get_name(), self.set_running)
        self.create_service(Empty, '/%s/go_home' % self.get_name(), self.go_home)
        self.create_service(SetBool, '/%s/set_self_balancing' % self.get_name(), self.set_self_balancing)
        self.create_service(SetRunActionName, '/%s/runActionGroup' % self.get_name(), self.run_action_group_fun)
        self.create_service(SetBool, '/%s/set_mark_time' % self.get_name(), self.set_mark_time)

        self.create_subscription(Gait, '/%s/gait' % self.get_name(), self.gait_fun, 10)
        self.create_subscription(Velocity, '/%s/velocity' % self.get_name(), self.velocity_fun, 10)
        self.create_subscription(Velocity, '/%s/velocity_move' % self.get_name(), self.velocity_move_fun, 10)
        self.create_subscription(Velocity, '/%s/velocity/autogait' % self.get_name(), self.velocity_autogait_fun, 10)
        self.create_subscription(Twist, '/cmd_vel', self.cmd_vel_fun, 10)
        self.create_subscription(Twist, '/cmd_vel_nav', self.cmd_vel_nav_fun, 10)
        self.create_subscription(Pose, '/%s/pose' % self.get_name(), self.pose_fun, 10)
        self.create_subscription(Polygon, '/%s/fourLegsRelativeCoordControl' % self.get_name(), self.four_legs_relative_coord_control_fun, 10)
        self.create_subscription(Float32MultiArray, '/%s/gait/pc' % self.get_name(), self.gait_pc_fun, 10)
        self.create_subscription(SetServo, '/%s/setServo' % self.get_name(), self.set_servo_fun, 10)

        self.legs_coord_pub = self.create_publisher(Polygon, '/%s/legs_coord' % self.get_name(), 10)
        self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)

        command_topics = [
            "/puppy/joint1_position_controller/command",
            "/puppy/joint2_position_controller/command",
            "/puppy/joint3_position_controller/command",
            "/puppy/joint4_position_controller/command",
            "/puppy/joint5_position_controller/command",
            "/puppy/joint6_position_controller/command",
            "/puppy/joint7_position_controller/command",
            "/puppy/joint8_position_controller/command"
        ]
        self.joint_controller_publishers = []
        for topic in command_topics:
            self.joint_controller_publishers.append(self.create_publisher(Float64, topic, 10))

        self.timer = self.create_timer(0.01, self.pub)

    def stance(self, x=0, y=0, z=-11, x_shift=2):
        return np.array([
            [x + x_shift, x + x_shift, -x + x_shift, -x + x_shift],
            [y, y, y, y],
            [z, z, z, z],
        ])

    def set_servo_fun(self, msg):
        if msg.pulse > 2500: msg.pulse = 2500
        if msg.pulse < 500: msg.pulse = 500
        if msg.time > 30000: msg.time = 30000

        setServoPulse(msg.id, msg.pulse, msg.time)

    def gait_fun(self, msg):
        global GaitConfig
        GaitConfig = dict(zip(GaitConfig.keys(), msg.__getstate__()))
        self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                               clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])

    def gait_pc_fun(self, msg):
        global GaitConfig
        if msg.data[0] == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        else:
            self.adjust_gait_config(msg)
            self.velocity_fun(Velocity(x=msg.data[3], y=msg.data[4], yaw_rate=msg.data[5]))

    def adjust_gait_config(self, msg):
        global GaitConfig
        if msg.data[0] == 1:  # Trot
            GaitConfig['overlap_time'] = msg.data[2] / 4
            GaitConfig['swing_time'] = msg.data[2] / 4
            GaitConfig['clearance_time'] = 0
        elif msg.data[0] == 2:  # Amble
            GaitConfig['overlap_time'] = msg.data[2] / 5
            GaitConfig['swing_time'] = msg.data[2] / 5
            GaitConfig['clearance_time'] = msg.data[2] / 10
        elif msg.data[0] == 3:  # Walk
            GaitConfig['overlap_time'] = msg.data[2] / 6
            GaitConfig['swing_time'] = msg.data[2] / 6
            GaitConfig['clearance_time'] = msg.data[2] / 6

        GaitConfig['z_clearance'] = msg.data[1]
        self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                               clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])

    def cmd_vel_fun(self, msg):
        global PuppyPose
        if abs(msg.linear.x) > 0.5 or abs(msg.angular.z) > 0.5:
            PuppyPose = Stand.copy()
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])

            if abs(msg.linear.x) > abs(msg.angular.z):
                self.velocity_fun(Velocity(16 * np.sign(msg.linear.x), 0, 0))
            else:
                self.velocity_fun(Velocity(0, 0, np.radians(25) * np.sign(msg.angular.z)))
        elif msg.linear.x == 0 and msg.angular.z == 0:
            self.velocity_fun(Velocity(0, 0, 0))

    def cmd_vel_nav_fun(self, msg):
        global PuppyPose
        PuppyPose = Stand.copy()
        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                 PuppyPose['pitch'], PuppyPose['roll'])
        self.velocity_fun(Velocity(msg.linear.x * 100, 0, msg.angular.z))

    def velocity_move_fun(self, msg):
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        else:
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_fun(self, msg):
        if msg.x == -999:  # Mark time
            self.puppy.move(x=0, y=0, yaw_rate=0)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        elif msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            if msg.x > 0:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift'] - 0.8),
                                         PuppyPose['pitch'], PuppyPose['roll'])
            else:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift'] + 0.8),
                                         PuppyPose['pitch'], PuppyPose['roll'])

            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_autogait_fun(self, msg):
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            self.adjust_autogait_config(msg)

            if msg.x > 0:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift'] - 0.8),
                                         PuppyPose['pitch'], PuppyPose['roll'])
            else:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift'] + 0.8),
                                         PuppyPose['pitch'], PuppyPose['roll'])

            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def adjust_autogait_config(self, msg):
        global GaitConfig
        if abs(msg.x) <= 10:
            overlap_time_x = 0.45 - abs(msg.x) * 0.023
            swing_time_x = 0.38 - abs(msg.x) * 0.0154
            clearance_time_x = swing_time_x - 0.04
        elif abs(msg.x) <= 15:
            overlap_time_x = 0.45 - abs(msg.x) * 0.023
            swing_time_x = 0.38 - abs(msg.x) * 0.0154
            clearance_time_x = 0
        else:
            overlap_time_x = 0.1
            swing_time_x = 0.15
            clearance_time_x = 0

        if abs(msg.yaw_rate) <= np.radians(10):
            overlap_time_yaw_rate = 0.23 - abs(msg.yaw_rate) * 0.37
            swing_time_yaw_rate = 0.36 - abs(msg.yaw_rate) * 0.74
            clearance_time_yaw_rate = swing_time_yaw_rate - 0.04
        elif abs(msg.yaw_rate) <= np.radians(20):
            overlap_time_yaw_rate = 0.23 - abs(msg.yaw_rate) * 0.37
            swing_time_yaw_rate = 0.41 - abs(msg.yaw_rate) * 0.74
            clearance_time_yaw_rate = 0
        else:
            overlap_time_yaw_rate = 0.1
            swing_time_yaw_rate = 0.15
            clearance_time_yaw_rate = 0

        GaitConfig['overlap_time'] = min(overlap_time_x, overlap_time_yaw_rate)
        GaitConfig['swing_time'] = min(swing_time_x, swing_time_yaw_rate)
        GaitConfig['clearance_time'] = min(clearance_time_x, clearance_time_yaw_rate)

        self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                               clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])

    def pose_fun(self, msg):
        # 添加日志，检查是否接收到消息
        self.get_logger().info(f"Received Pose message: roll={msg.roll}, pitch={msg.pitch}, yaw={msg.yaw}, height={msg.height}, x_shift={msg.x_shift}, stance_x={msg.stance_x}, stance_y={msg.stance_y}, run_time={msg.run_time}")
        
        # 原有的逻辑处理
        global PuppyPose
        if (abs(msg.roll) <= np.radians(31) and abs(msg.pitch) <= np.radians(31) 
                and abs(msg.yaw) == 0 and msg.height >= -15 and msg.height <= -5
                and abs(msg.stance_x) <= 5 and abs(msg.stance_y) <= 5
                and abs(msg.x_shift) <= 10):

            if msg.run_time != 0:
                self.puppy.move_stop(servo_run_time=msg.run_time)
                self.get_logger().info("Puppy Stopping")
                self.puppy.servo_force_run()

            PuppyPose = dict(zip(PuppyPose.keys(), msg.__getstate__()[:-1]))
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                    PuppyPose['pitch'], PuppyPose['roll'])

    def four_legs_relative_coord_control_fun(self, msg):
        rotated_foot_locations = np.zeros((3, 4))
        for idx, p in enumerate(msg.points):
            rotated_foot_locations[:, idx] = p.x, p.y, p.z

        joint_angles = self.puppy.fourLegsRelativeCoordControl(rotated_foot_locations)
        self.puppy.sendServoAngle(joint_angles)

    def run_action_group_fun(self, request, response):
        self.get_logger().info(f'Running action group: {request.name}')
        runActionGroup(request.name, request.wait)
        response.success = True
        response.name = request.name
        return response

    def pub(self):
        times = 0
        while rclpy.ok():
            coord = self.puppy.get_coord()

            if times >= 100:
                times = 0
                msg = Polygon()
                msg.points = [Point32(x=coord[0, i], y=coord[1, i], z=coord[2, i]) for i in range(4)]
                self.legs_coord_pub.publish(msg)

                joint_angles = self.puppy.fourLegsRelativeCoordControl(coord / 100)
                data = sum([list(joint_angles[1, :]), list(joint_angles[2, :])], [])

                self.joint_state.header.stamp = self.get_clock().now().to_msg()
                for i in range(len(data)):
                    if i > 3:
                        data[i] = 0.0695044662 * data[i] ** 3 - 0.0249173454 * data[i] ** 2 - 0.786456081 * data[i] + 1.5443387652 - 3.1415926 / 2
                    if self.joint_state_controller_pub_topic:
                        self.joint_controller_publishers[i].publish(Float64(data=data[i]))

                if self.joint_state_pub_topic:
                    self.joint_state.position = data 
                    self.joint_state_pub.publish(self.joint_state)

            times += 1
            rclpy.spin_once(self)

    def set_running(self, request, response):
        if request.data:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.start()
            response.success = True
        else:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.end()
            response.success = True
        return response
        
    def set_self_balancing(self, request, response):
        if request.data:
            global PuppyPose
            PuppyPose = Stand.copy()
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                     PuppyPose['pitch'], PuppyPose['roll'])
        
            self.puppy.move_stop(servo_run_time=500)
            time.sleep(0.01)
            self.puppy.servo_force_run()
            time.sleep(0.5)
            self.puppy.move_stop(servo_run_time=0)
            self.puppy.imu = self.mpu
        else:
            self.puppy.imu = None
        response.success = True
        return response

    def set_mark_time(self, request, response):
        if request.data:
            self.go_home()
            global GaitConfig
            GaitConfig = GaitConfigMarkTime.copy()
            self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                                   clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])
            self.puppy.move(x=0, y=0, yaw_rate=0)
        response.success = True
        return response

    def go_home(self, request=None, response=None):
        global PuppyPose
        PuppyPose = Stand.copy()
        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']),
                                 PuppyPose['pitch'], PuppyPose['roll'])

        self.puppy.move_stop(servo_run_time=500)
        time.sleep(0.01)
        self.puppy.servo_force_run()
        time.sleep(0.5)
        self.puppy.move_stop(servo_run_time=0)
        if response is not None:
            return response


def main(args=None):
    rclpy.init(args=args)
    puppy_node = PUPPY()
    rclpy.spin(puppy_node)

    puppy_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()


