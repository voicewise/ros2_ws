#!/usr/bin/python3
# coding=utf8
# Author:Summer
# Email:997950600@qq.com

import os
import sys
import math
import time
import numpy as np

import rclpy
from rclpy.node import Node

from std_msgs.msg import UInt8, UInt16, Float32, Float64, Bool, String, Float32MultiArray
from std_srvs.srv import Empty, SetBool
from ros_robot_controller_msgs.msg import BuzzerState
from geometry_msgs.msg import Point32, Polygon, Twist
from puppy_control_msgs.msg import Velocity, Pose, Gait, SetServo
from puppy_control_msgs.srv import SetRunActionName
from sensor_msgs.msg import Imu, JointState

from sdk.ArmMoveIK import *

ROS_NODE_NAME = 'puppy_control'

sys.path.append('/home/ubuntu/software/puppypi_control')
from servo_controller import setServoPulse, updatePulse
from action_group_control import runActionGroup, stopActionGroup

from puppy_kinematics import HiwonderPuppy, PWMServoParams

with_arm = 0
if with_arm:
    offset = 0.1
else:
    offset = 0

Stand = {'roll': math.radians(0), 'pitch': math.radians(0), 'yaw': 0.000, 'height': -10, 'x_shift': -0.5 + offset, 'stance_x': 0, 'stance_y': 0}
LieDown = {'roll': 0.000, 'pitch': 0.000, 'yaw': 0.000, 'height': -5, 'x_shift': 2, 'stance_x': 0, 'stance_y': 0}
LookDown = {'roll': math.radians(0), 'pitch': math.radians(-15), 'yaw': 0.000, 'height': -10, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0}
LookDown_10deg = {'roll': math.radians(0), 'pitch': math.radians(-10), 'yaw': 0.000, 'height': -9, 'x_shift': -0.1, 'stance_x': 0, 'stance_y': 0}
LookDown_20deg = {'roll': math.radians(0), 'pitch': math.radians(-20), 'yaw': 0.000, 'height': -9, 'x_shift': -0.1, 'stance_x': 0, 'stance_y': 0}
LookDown_30deg = {'roll': math.radians(0), 'pitch': math.radians(-30), 'yaw': 0.000, 'height': -9.6, 'x_shift': -1.4, 'stance_x': 1, 'stance_y': 0}

StandLow = {'roll': math.radians(0), 'pitch': math.radians(0), 'yaw': 0.000, 'height': -7, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0}
PuppyPose = LieDown.copy()

GaitConfigFast = {'overlap_time': 0.1, 'swing_time': 0.15, 'clearance_time': 0.0, 'z_clearance': 5}
GaitConfigSlow = {'overlap_time': 0.4, 'swing_time': 0.3, 'clearance_time': 0.26, 'z_clearance': 4}
GaitConfigMarkTime = {'overlap_time': 0.2, 'swing_time': 0.1, 'clearance_time': 0.0, 'z_clearance': 5}
GaitConfig = GaitConfigFast.copy()

class MPU6050():
    def __init__(self, node):
        self.node = node
        self.node.create_subscription(Imu, '/ros_robot_controller/imu_raw', self.GetImuFun, 10)
        self.data = {'accel': [0, 0, 0], 'gyro': [0, 0, 0]}
        self.SecondOrderFilterX = self._SecondOrderFilter()
        self.SecondOrderFilterY = self._SecondOrderFilter()

    def GetImuFun(self, msg):
        self.data['accel'][0] = msg.linear_acceleration.x
        self.data['accel'][1] = msg.linear_acceleration.y
        self.data['accel'][2] = msg.linear_acceleration.z
        self.data['gyro'][0] = msg.angular_velocity.x
        self.data['gyro'][1] = msg.angular_velocity.y
        self.data['gyro'][2] = msg.angular_velocity.z

    def _SecondOrderFilter(self):
        x1 = 0
        x2 = 0
        y1 = 0
        angle = 0
        K2 = 0.02

        def fun(angle_m, gyro_m, dt=0.01):
            nonlocal x1
            nonlocal x2
            nonlocal y1
            nonlocal angle
            nonlocal K2
            x1 = (angle_m - angle) * (1 - K2) * (1 - K2)
            y1 = y1 + x1 * dt
            x2 = y1 + 2 * (1 - K2) * (angle_m - angle) + gyro_m
            angle = angle + x2 * dt
            return angle

        return fun

    def get_euler_angle(self, dt=0.01):
        data = self.data
        accel_Y = math.atan2(data['accel'][0], data['accel'][2]) * 180 / math.pi
        gyro_Y = data['gyro'][1]
        angleY = self.SecondOrderFilterY(-accel_Y, gyro_Y, dt)

        accel_X = math.atan2(data['accel'][1], data['accel'][2]) * 180 / math.pi
        gyro_X = data['gyro'][0]
        angleX = self.SecondOrderFilterX(accel_X, gyro_X, dt)

        return {'pitch': -math.radians(angleX), 'roll': -math.radians(angleY), 'yaw': 0}

class PUPPY(Node):
    def __init__(self):
        super().__init__(ROS_NODE_NAME)

        # Declare parameters
        self.declare_parameter('joint_state_pub_topic', False)
        self.declare_parameter('joint_state_controller_pub_topic', False)

        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').value

        self.puppy = HiwonderPuppy(setServoPulse=setServoPulse, servoParams=PWMServoParams(), dof='8')
        self.mpu = MPU6050(self)
        self.puppy.imu = None  # self.mpu

        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                               clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])
        self.puppy.start()  # 启动
        self.puppy.move_stop(servo_run_time=500)  #
        self.ak = ArmIK()
        self.ak.setPitchRangeMoving((8.51, 0, 3.3), 500)
        time.sleep(0.5)
        setServoPulse(9, 1500, 300)
        time.sleep(0.3)

        # 将姿态和步态配置存储为实例变量
        self.PuppyPoseConfigs = {
            'Stand': Stand,
            'LieDown': LieDown,
            'LookDown': LookDown,
            'LookDown_10deg': LookDown_10deg,
            'LookDown_20deg': LookDown_20deg,
            'LookDown_30deg': LookDown_30deg,
            'StandLow': StandLow
        }

        self.GaitConfigs = {
            'GaitConfigFast': GaitConfigFast,
            'GaitConfigSlow': GaitConfigSlow
        }

        # Services
        self.create_service(SetBool, '/%s/set_running' % ROS_NODE_NAME, self.set_running)
        self.create_service(Empty, '/%s/go_home' % ROS_NODE_NAME, self.go_home)
        self.create_service(SetBool, '/%s/set_self_balancing' % ROS_NODE_NAME, self.set_self_balancing)
        self.create_service(SetRunActionName, '/%s/runActionGroup' % ROS_NODE_NAME, self.runActionGroupFun)
        self.create_service(SetBool, '/%s/set_mark_time' % ROS_NODE_NAME, self.set_mark_time)

        # Subscribers
        self.create_subscription(Gait, '/%s/gait' % ROS_NODE_NAME, self.GaitFun, 10)
        self.create_subscription(Velocity, '/%s/velocity' % ROS_NODE_NAME, self.VelocityFun, 10)
        self.create_subscription(Velocity, '/%s/velocity_move' % ROS_NODE_NAME, self.VelocityMoveFun, 10)
        self.create_subscription(Velocity, '/%s/velocity/autogait' % ROS_NODE_NAME, self.VelocityAutogaitFun, 10)
        self.create_subscription(Twist, '/cmd_vel', self.Cmd_velFun, 10)
        self.create_subscription(Twist, '/cmd_vel_nav', self.Cmd_vel_nav_Fun, 10)
        self.create_subscription(Pose, '/%s/pose' % ROS_NODE_NAME, self.PoseFun, 10)
        self.create_subscription(Polygon, '/%s/fourLegsRelativeCoordControl' % ROS_NODE_NAME, self.fourLegsRelativeCoordControlFun, 10)
        self.create_subscription(Float32MultiArray, '/%s/gait/pc' % ROS_NODE_NAME, self.GaitPCFun, 10)
        self.create_subscription(SetServo, '/%s/setServo' % ROS_NODE_NAME, self.SetServo_Fun, 10)

        # Publishers
        self.legs_coord_pub = self.create_publisher(Polygon, '/%s/legs_coord' % ROS_NODE_NAME, 10)
        self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)

        self.joint_state = JointState()
        self.joint_state.name = ['rf_joint1', 'lf_joint1', 'rb_joint1', 'lb_joint1', 'rf_joint2', 'lf_joint2', 'rb_joint2', 'lb_joint2']

        command_topics = ["/puppy/joint1_position_controller/command",
                          "/puppy/joint2_position_controller/command",
                          "/puppy/joint3_position_controller/command",
                          "/puppy/joint4_position_controller/command",
                          "/puppy/joint5_position_controller/command",
                          "/puppy/joint6_position_controller/command",
                          "/puppy/joint7_position_controller/command",
                          "/puppy/joint8_position_controller/command"]

        self.joint_controller_publishers = []
        for topic in command_topics:
            self.joint_controller_publishers.append(self.create_publisher(Float64, topic, 10))

        self.timer = self.create_timer(0.01, self.pub_callback)  # 100hz

        # Buzzer publisher
        self.buzzer_pub = self.create_publisher(BuzzerState, '/ros_robot_controller/set_buzzer', 10)
        time.sleep(0.2)
        msg = BuzzerState()
        msg.freq = 1900
        msg.on_time = 0.1
        msg.off_time = 0.9
        msg.repeat = 1
        self.buzzer_pub.publish(msg)

    def stance(self, x=0, y=0, z=-11, x_shift=2):
        return np.array([
            [x + x_shift, x + x_shift, -x + x_shift, -x + x_shift],
            [y, y, y, y],
            [z, z, z, z],
        ])

    def SetServo_Fun(self, msg):
        if msg.pulse > 2500:
            msg.pulse = 2500
        if msg.pulse < 500:
            msg.pulse = 500
        if msg.time > 30000:
            msg.time = 30000

        setServoPulse(msg.id, msg.pulse, msg.time)

    def GaitFun(self, msg):
        global GaitConfig
        self.get_logger().debug(str(msg))
        GaitConfig = {
            'overlap_time': msg.overlap_time,
            'swing_time': msg.swing_time,
            'clearance_time': msg.clearance_time,
            'z_clearance': msg.z_clearance
        }
        self.puppy.gait_config(
            overlap_time=GaitConfig['overlap_time'],
            swing_time=GaitConfig['swing_time'],
            clearance_time=GaitConfig['clearance_time'],
            z_clearance=GaitConfig['z_clearance'])


    def GaitPCFun(self, msg):
        global GaitConfig
        self.get_logger().debug(str(msg))
        if msg.data[0] == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'], PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        else:
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
            self.VelocityFun(Velocity(x=msg.data[3], y=msg.data[4], yaw_rate=msg.data[5]))

    def Cmd_velFun(self, msg):
        global PuppyPose
        self.get_logger().debug(str(msg))

        if abs(msg.linear.x) > 0.5 or abs(msg.angular.z) > 0.5:
            PuppyPose = Stand.copy()
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])

            if abs(msg.linear.x) > abs(msg.angular.z):
                self.VelocityFun(Velocity(16 * np.sign(msg.linear.x), 0, 0))
            else:
                self.VelocityFun(Velocity(0, 0, np.radians(25) * np.sign(msg.angular.z)))
        elif msg.linear.x == 0 and msg.angular.z == 0:
            self.VelocityFun(Velocity(0, 0, 0))

    def Cmd_vel_nav_Fun(self, msg):
        global PuppyPose
        PuppyPose = Stand.copy()
        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                             PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        self.VelocityFun(Velocity(msg.linear.x * 100, 0, msg.angular.z))

    def VelocityMoveFun(self, msg):
        self.get_logger().debug(str(msg))
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        else:
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def VelocityFun(self, msg):
        self.get_logger().debug(str(msg))
        if msg.x == -999:  # 原地踏步
            self.puppy.move(x=0, y=0, yaw_rate=0)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        elif msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            if msg.x > 0:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                     PuppyPose['height'], PuppyPose['x_shift'] - 0.8), PuppyPose['pitch'], PuppyPose['roll'])
            else:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                     PuppyPose['height'], PuppyPose['x_shift'] + 0.8), PuppyPose['pitch'], PuppyPose['roll'])

            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def VelocityAutogaitFun(self, msg):
        self.get_logger().debug(str(msg))
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
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
            if abs(msg.yaw_rate) <= np.radians(20):
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

            if msg.x > 0:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                     PuppyPose['height'], PuppyPose['x_shift'] - 0.8), PuppyPose['pitch'], PuppyPose['roll'])
            else:
                self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                     PuppyPose['height'], PuppyPose['x_shift'] + 0.8), PuppyPose['pitch'], PuppyPose['roll'])

            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    
    def PoseFun(self, msg):
        global PuppyPose
        self.get_logger().debug(str(msg))
        if (abs(msg.roll) <= np.radians(31) and abs(msg.pitch) <= np.radians(31)
                and abs(msg.yaw) == 0 and msg.height >= -15 and msg.height <= -5
                and abs(msg.stance_x) <= 5 and abs(msg.stance_y) <= 5
                and abs(msg.x_shift) <= 10):

            if msg.run_time != 0:
                self.puppy.move_stop(servo_run_time=msg.run_time)
                time.sleep(0.01)
                self.puppy.servo_force_run()

            PuppyPose = {
                'roll': msg.roll,
                'pitch': msg.pitch,
                'yaw': msg.yaw,
                'height': msg.height,
                'x_shift': msg.x_shift,
                'stance_x': msg.stance_x,
                'stance_y': msg.stance_y
            }
            self.puppy.stance_config(self.stance(
                PuppyPose['stance_x'], PuppyPose['stance_y'],
                PuppyPose['height'], PuppyPose['x_shift']),
                PuppyPose['pitch'], PuppyPose['roll'])

    def fourLegsRelativeCoordControlFun(self, msg):
        self.get_logger().debug(str(msg))
        rotated_foot_locations = np.zeros((3, 4))
        for idx, p in enumerate(msg.points):
            rotated_foot_locations[:, idx] = p.x, p.y, p.z

        joint_angles = self.puppy.fourLegsRelativeCoordControl(rotated_foot_locations)
        self.puppy.sendServoAngle(joint_angles)

    def runActionGroupFun(self, request, response):
        self.get_logger().debug(str(request))
        runActionGroup(request.name, request.wait)
        response.success = True
        response.message = request.name
        return response

    def pub_callback(self):
        coord = self.puppy.get_coord()
        msg = Polygon()
        msg.points = []
        for x, y, z in zip(coord[0, :], coord[1, :], coord[2, :]):
            point = Point32()
            point.x = x
            point.y = y
            point.z = z
            msg.points.append(point)
        self.legs_coord_pub.publish(msg)

        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').value

        if self.joint_state_pub_topic or self.joint_state_controller_pub_topic:
            joint_angles = self.puppy.fourLegsRelativeCoordControl(coord / 100)
            data = sum([list(joint_angles[1, :]), list(joint_angles[2, :])], [])
            self.joint_state.header.stamp = self.get_clock().now().to_msg()
            for i in range(len(data)):
                if i > 3:
                    data[i] = (
                        0.0695044662 * data[i] ** 3
                        - 0.0249173454 * data[i] ** 2
                        - 0.786456081 * data[i]
                        + 1.5443387652
                        - 3.1415926 / 2
                    )
                if self.joint_state_controller_pub_topic:
                    self.joint_controller_publishers[i].publish(Float64(data[i]))
            if self.joint_state_pub_topic:
                self.joint_state.position = data
                self.joint_state_pub.publish(self.joint_state)


    def set_running(self, request, response):
        self.get_logger().debug(str(request))
        if request.data:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.start()
        else:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.end()
        response.success = True
        response.message = 'set_running'
        return response

    def set_self_balancing(self, request, response):
        self.get_logger().debug(str(request))
        if request.data:
            PuppyPose = Stand.copy()
            self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                                 PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])

            self.puppy.move_stop(servo_run_time=500)
            time.sleep(0.01)
            self.puppy.servo_force_run()
            time.sleep(0.5)
            self.puppy.move_stop(servo_run_time=0)
            self.puppy.imu = self.mpu
        else:
            self.puppy.imu = None
        response.success = True
        response.message = 'set_self_balancing'
        return response

    def set_mark_time(self, request, response):
        self.get_logger().debug(str(request))
        if request.data:
            self.go_home(None, None)
            GaitConfig = GaitConfigMarkTime.copy()
            self.puppy.gait_config(overlap_time=GaitConfig['overlap_time'], swing_time=GaitConfig['swing_time'],
                                   clearance_time=GaitConfig['clearance_time'], z_clearance=GaitConfig['z_clearance'])
            self.puppy.move(x=0, y=0, yaw_rate=0)
        else:
            pass
        response.success = True
        response.message = 'set_mark_time'
        return response

    def go_home(self, request, response):
        global PuppyPose
        self.get_logger().debug('go_home')
        PuppyPose = Stand.copy()
        self.puppy.stance_config(self.stance(PuppyPose['stance_x'], PuppyPose['stance_y'],
                                             PuppyPose['height'], PuppyPose['x_shift']), PuppyPose['pitch'], PuppyPose['roll'])

        self.puppy.move_stop(servo_run_time=500)
        time.sleep(0.01)
        self.puppy.servo_force_run()
        time.sleep(0.5)
        self.puppy.move_stop(servo_run_time=0)
        if response:
            return response

def main(args=None):
    rclpy.init(args=args)
    puppy = PUPPY()
    try:
        rclpy.spin(puppy)
    except KeyboardInterrupt:
        pass
    finally:
        puppy.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
