#!/usr/bin/python3
# coding=utf8
# Author: Summer
# Email: 997950600@qq.com

import time
import os
import sys
import math
import numpy as np
import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt8, UInt16, Float32, Float64, Bool, String, Float32MultiArray
from std_srvs.srv import Empty, SetBool
from ros_robot_controller_msgs.msg import BuzzerState
from geometry_msgs.msg import Point32, Polygon, Twist
from puppy_control_msgs.srv import SetRunActionName
from sensor_msgs.msg import Imu, JointState
from puppy_control_msgs.msg import Velocity, Gait, SetServo, Pose
from rclpy.duration import Duration

sys.path.append('/home/ubuntu/software/puppypi_control')
from servo_controller import setServoPulse, updatePulse
from action_group_control import runActionGroup, stopActionGroup
from puppy_kinematics import HiwonderPuppy, PWMServoParams

# Define global pose configurations
with_arm = 0
offset = 0.1 if with_arm else 0

# Pose Definitions
POSES = {
    'Stand': {'roll': 0.0, 'pitch': 0.0, 'yaw': 0.0, 'height': -10, 'x_shift': -0.5 + offset, 'stance_x': 0, 'stance_y': 0},
    'LieDown': {'roll': 0.0, 'pitch': 0.0, 'yaw': 0.0, 'height': -5, 'x_shift': 2, 'stance_x': 0, 'stance_y': 0},
    'LookDown': {'roll': 0.0, 'pitch': -math.radians(15), 'yaw': 0.0, 'height': -10, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0},
    'LookDown_10deg': {'roll': 0.0, 'pitch': -math.radians(10), 'yaw': 0.0, 'height': -9, 'x_shift': -0.1, 'stance_x': 0, 'stance_y': 0},
    'LookDown_20deg': {'roll': 0.0, 'pitch': -math.radians(20), 'yaw': 0.0, 'height': -9, 'x_shift': -0.1, 'stance_x': 0, 'stance_y': 0},
    'LookDown_30deg': {'roll': 0.0, 'pitch': -math.radians(30), 'yaw': 0.0, 'height': -9.6, 'x_shift': -1.4, 'stance_x': 1, 'stance_y': 0},
    'StandLow': {'roll': 0.0, 'pitch': 0.0, 'yaw': 0.0, 'height': -7, 'x_shift': -0.5, 'stance_x': 0, 'stance_y': 0},
}

# Gait Configurations
GAIT_CONFIGS = {
    'Fast': {'overlap_time': 0.1, 'swing_time': 0.15, 'clearance_time': 0.0, 'z_clearance': 5},
    'Slow': {'overlap_time': 0.4, 'swing_time': 0.3, 'clearance_time': 0.26, 'z_clearance': 4},
    'MarkTime': {'overlap_time': 0.2, 'swing_time': 0.1, 'clearance_time': 0.0, 'z_clearance': 5},
}


class MPU6050:
    def __init__(self, node):
        self.node = node
        self.data = {'accel': [0, 0, 0], 'gyro': [0, 0, 0]}
        self.SecondOrderFilterX = self._SecondOrderFilter()
        self.SecondOrderFilterY = self._SecondOrderFilter()
        self.subscriber = self.node.create_subscription(Imu, '/ros_robot_controller/imu_raw', self.GetImuFun, 10)

    def GetImuFun(self, msg):
        self.data['accel'] = [msg.linear_acceleration.x, msg.linear_acceleration.y, msg.linear_acceleration.z]
        self.data['gyro'] = [msg.angular_velocity.x, msg.angular_velocity.y, msg.angular_velocity.z]

    def _SecondOrderFilter(self):
        x1, x2, y1, angle, K2 = 0, 0, 0, 0, 0.02

        def fun(angle_m, gyro_m, dt=0.01):
            nonlocal x1, x2, y1, angle, K2
            x1 = (angle_m - angle) * (1 - K2) ** 2
            y1 += x1 * dt
            x2 = y1 + 2 * (1 - K2) * (angle_m - angle) + gyro_m
            angle += x2 * dt
            return angle

        return fun

    def get_euler_angle(self, dt=0.01):
        accel_Y = math.atan2(self.data['accel'][0], self.data['accel'][2]) * 180 / math.pi
        gyro_Y = self.data['gyro'][1]
        angleY = self.SecondOrderFilterY(-accel_Y, gyro_Y, dt)

        accel_X = math.atan2(self.data['accel'][1], self.data['accel'][2]) * 180 / math.pi
        gyro_X = self.data['gyro'][0]
        angleX = self.SecondOrderFilterX(accel_X, gyro_X, dt)

        return {'pitch': -math.radians(angleX), 'roll': -math.radians(angleY), 'yaw': 0}


class PUPPY(Node):
    def __init__(self):
        super().__init__('puppy_control')
        self.init_params()  # Initialize parameters
        self.puppy = self.init_puppy()
        self.mpu = MPU6050(self)
        self.puppy.imu = None
        self.init_services_and_subscribers()
        self.init_publishers()
        self.init_buzzer()
        self.create_timer(0.01, self.pub)


    def init_params(self):
        """声明和设置参数"""
        # 声明参数
        self.declare_parameters(
            namespace='',
            parameters=[
                ('joint_state_pub_topic', 'false'),
                ('joint_state_controller_pub_topic', 'false'),
                ('PuppyPose', str(POSES)),  # 直接将POSES作为字符串传入
                ('GaitConfig', str(GAIT_CONFIGS))  # 直接将GAIT_CONFIGS作为字符串传入
            ]
        )
        
        # 获取参数值
        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').get_parameter_value().string_value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').get_parameter_value().string_value
        
        # 输出参数值到日志，确保参数设置正确
        self.get_logger().info(f"PuppyPose Param: {POSES}")
        self.get_logger().info(f"GaitConfig Param: {GAIT_CONFIGS}")
        
        # 初始化姿态和步态配置
        self.PuppyPose = POSES['LieDown'].copy()
        self.GaitConfig = GAIT_CONFIGS['Fast'].copy()


    def set_parameters(self):
        self.set_parameters([
            rclpy.parameter.Parameter(
                'PuppyPose',
                rclpy.Parameter.Type.STRING,
                str(POSES)
            ),
            rclpy.parameter.Parameter(
                'GaitConfig',
                rclpy.Parameter.Type.STRING,
                str(GAIT_CONFIGS)
            ),
        ])
        self.get_logger().info(f"PuppyPose Param: {POSES}")
        self.get_logger().info(f"GaitConfig Param: {GAIT_CONFIGS}")

    def init_puppy(self):
        puppy = HiwonderPuppy(setServoPulse=setServoPulse, servoParams=PWMServoParams(), dof='8')
        puppy.stance_config(self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']), 
                            self.PuppyPose['pitch'], self.PuppyPose['roll'])
        puppy.gait_config(overlap_time=self.GaitConfig['overlap_time'], swing_time=self.GaitConfig['swing_time'], 
                          clearance_time=self.GaitConfig['clearance_time'], z_clearance=self.GaitConfig['z_clearance'])
        puppy.start()
        puppy.move_stop(servo_run_time=500)
        return puppy

    def init_services_and_subscribers(self):
        self.create_service(SetBool, '/puppy_control/set_running', self.set_running)
        self.create_service(Empty, '/puppy_control/go_home', self.go_home)
        self.create_service(SetBool, '/puppy_control/set_self_balancing', self.set_self_balancing)
        self.create_service(SetRunActionName, '/puppy_control/runActionGroup', self.runActionGroupFun)
        self.create_service(SetBool, '/puppy_control/set_mark_time', self.set_mark_time)

        self.create_subscription(Gait, '/puppy_control/gait', self.GaitFun,        10)
        self.create_subscription(Velocity, '/puppy_control/velocity', self.VelocityFun, 10)
        self.create_subscription(Velocity, '/puppy_control/velocity_move', self.VelocityMoveFun, 10)
        self.create_subscription(Velocity, '/puppy_control/velocity/autogait', self.VelocityAutogaitFun, 10)
        self.create_subscription(Twist, '/cmd_vel', self.Cmd_velFun, 10)
        self.create_subscription(Twist, '/cmd_vel_nav', self.Cmd_vel_nav_Fun, 10)
        self.create_subscription(Pose, '/puppy_control/pose', self.PoseFun, 10)
        self.create_subscription(Polygon, '/puppy_control/fourLegsRelativeCoordControl', self.fourLegsRelativeCoordControlFun, 10)
        self.create_subscription(Float32MultiArray, '/puppy_control/gait/pc', self.GaitPCFun, 10)
        self.create_subscription(SetServo, '/puppy_control/setServo', self.SetServo_Fun, 10)

    def init_publishers(self):
        self.legs_coord_pub = self.create_publisher(Polygon, '/puppy_control/legs_coord', 10)
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

        self.joint_controller_publishers = [self.create_publisher(Float64, topic, 10) for topic in command_topics]

    def init_buzzer(self):
        buzzer_pub = self.create_publisher(BuzzerState, '/ros_robot_controller/set_buzzer', 1)
        self.get_clock().sleep_for(Duration(seconds=0.2))
        msg = BuzzerState(freq=1900, on_time=0.1, off_time=0.9, repeat=1)
        buzzer_pub.publish(msg)

    def stance(self, x=0, y=0, z=-11, x_shift=2):
        return np.array([
            [x + x_shift, x + x_shift, -x + x_shift, -x + x_shift],
            [y, y, y, y],
            [z, z, z, z],
        ])

    def SetServo_Fun(self, msg):
        pulse = min(max(msg.pulse, 500), 2500)
        time = min(msg.time, 30000)
        setServoPulse(msg.id, pulse, time)

    def GaitFun(self, msg):
        self.update_gait_config(overlap_time=msg.overlap_time, swing_time=msg.swing_time,
                                clearance_time=msg.clearance_time, z_clearance=msg.z_clearance)

    def GaitPCFun(self, msg):
        self.get_logger().info(f"Received GaitPC: {msg}")
        if msg.data[0] == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.reset_stance()
        else:
            self.set_gait_from_pc_data(msg.data)
            self.VelocityFun(Velocity(x=msg.data[3], y=msg.data[4], yaw_rate=msg.data[5]))

    def set_gait_from_pc_data(self, data):
        if data[0] == 1:  # Trot
            overlap_time = swing_time = data[2] / 4
            clearance_time = 0
        elif data[0] == 2:  # Amble
            overlap_time = swing_time = data[2] / 5
            clearance_time = data[2] / 10
        elif data[0] == 3:  # Walk
            overlap_time = swing_time = clearance_time = data[2] / 6
        else:
            return

        z_clearance = data[1]
        self.update_gait_config(overlap_time, swing_time, clearance_time, z_clearance)

    def update_gait_config(self, overlap_time, swing_time, clearance_time, z_clearance):
        self.GaitConfig.update({
            'overlap_time': overlap_time,
            'swing_time': swing_time,
            'clearance_time': clearance_time,
            'z_clearance': z_clearance
        })
        self.puppy.gait_config(overlap_time=overlap_time, swing_time=swing_time, 
                            clearance_time=clearance_time, z_clearance=z_clearance)


    def reset_stance(self):
        self.puppy.stance_config(
            self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
            self.PuppyPose['pitch'], self.PuppyPose['roll'])

    def Cmd_velFun(self, msg):
        self.get_logger().info(f"Received cmd_vel: {msg}")
        self.handle_velocity_command(msg.linear.x, msg.angular.z)

    def Cmd_vel_nav_Fun(self, msg):
        self.get_logger().info(f"Received cmd_vel_nav: {msg}")
        self.PuppyPose = POSES['Stand'].copy()
        self.reset_stance()
        self.VelocityFun(Velocity(msg.linear.x * 100, 0, msg.angular.z))

    def handle_velocity_command(self, linear_x, angular_z):
        if abs(linear_x) > 0.5 or abs(angular_z) > 0.5:
            self.PuppyPose = POSES['Stand'].copy()
            self.reset_stance()
            velocity = Velocity(16 * np.sign(linear_x), 0, 0) if abs(linear_x) > abs(angular_z) else Velocity(0, 0, np.radians(25) * np.sign(angular_z))
            self.VelocityFun(velocity)
        elif linear_x == 0 and angular_z == 0:
            self.VelocityFun(Velocity(0, 0, 0))

    def VelocityMoveFun(self, msg):
        self.get_logger().info(f"Received VelocityMove: {msg}")
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.reset_stance()
        else:
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def VelocityFun(self, msg):
        self.get_logger().info(f"Received Velocity: {msg}")
        if msg.x == -999:  # On the spot
            self.puppy.move(x=0, y=0, yaw_rate=0)
            self.reset_stance()
        elif msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.reset_stance()
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            x_shift = self.PuppyPose['x_shift'] - 0.8 if msg.x > 0 else self.PuppyPose['x_shift'] + 0.8
            self.puppy.stance_config(self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'],
                                                 self.PuppyPose['height'], x_shift),
                                     self.PuppyPose['pitch'], self.PuppyPose['roll'])
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def VelocityAutogaitFun(self, msg):
        self.get_logger().info(f"Received VelocityAutogait: {msg}")
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.reset_stance()
        else:
            overlap_time_x, swing_time_x, clearance_time_x = self.calculate_gait_parameters(msg.x)
            overlap_time_yaw_rate, swing_time_yaw_rate, clearance_time_yaw_rate = self.calculate_gait_parameters(msg.yaw_rate, is_yaw=True)

            self.update_gait_config(min(overlap_time_x, overlap_time_yaw_rate),
                                    min(swing_time_x, swing_time_yaw_rate),
                                    min(clearance_time_x, clearance_time_yaw_rate),
                                    self.GaitConfig['z_clearance'])

            x_shift = self.PuppyPose['x_shift'] - 0.8 if msg.x > 0 else self.PuppyPose['x_shift'] + 0.8
            self.puppy.stance_config(self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'],
                                                 self.PuppyPose['height'], x_shift),
                                     self.PuppyPose['pitch'], self.PuppyPose['roll'])
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def calculate_gait_parameters(self, value, is_yaw=False):
        """计算步态参数，根据速度或偏航率调整步态参数"""
        if is_yaw:
            if abs(value) <= np.radians(10):
                overlap_time = 0.23 - abs(value) * 0.37
                swing_time = 0.36 - abs(value) * 0.74
                clearance_time = swing_time - 0.04
            elif abs(value) <= np.radians(20):
                overlap_time = 0.23 - abs(value) * 0.37
                swing_time = 0.41 - abs(value) * 0.74
                clearance_time = 0
            else:
                overlap_time, swing_time, clearance_time = 0.1, 0.15, 0
        else:
            if abs(value) <= 10:
                overlap_time = 0.45 - abs(value) * 0.023
                swing_time = 0.38 - abs(value) * 0.0154
                clearance_time = swing_time - 0.04
            elif abs(value) <= 15:
                overlap_time = 0.45 - abs(value) * 0.023
                swing_time = 0.38 - abs(value) * 0.0154
                clearance_time = 0
            else:
                overlap_time, swing_time, clearance_time = 0.1, 0.15, 0

        return overlap_time, swing_time, clearance_time

    def PoseFun(self, msg):
        """处理姿态控制消息"""
        self.get_logger().info(f"Received Pose: {msg}")

        if (abs(msg.roll) <= math.radians(31) and abs(msg.pitch) <= math.radians(31) 
                and abs(msg.yaw) == 0 and -15 <= msg.height <= -5
                and abs(msg.stance_x) <= 5 and abs(msg.stance_y) <= 5
                and abs(msg.x_shift) <= 10):

            if msg.run_time != 0:
                self.puppy.move_stop(servo_run_time=msg.run_time)
                self.get_clock().sleep_for(Duration(seconds=0.01))
                self.puppy.servo_force_run()

            # 更新Puppy姿态配置
            self.PuppyPose.update({'roll': msg.roll, 'pitch': msg.pitch, 'yaw': msg.yaw,
                                   'height': msg.height, 'x_shift': msg.x_shift,
                                   'stance_x': msg.stance_x, 'stance_y': msg.stance_y})
            self.reset_stance()

    def fourLegsRelativeCoordControlFun(self, msg):
        """处理四足相对坐标控制消息"""
        self.get_logger().info(f"Received fourLegsRelativeCoordControl: {msg}")
        rotated_foot_locations = np.array([[p.x, p.y, p.z] for p in msg.points]).T

        joint_angles = self.puppy.fourLegsRelativeCoordControl(rotated_foot_locations)
        self.puppy.sendServoAngle(joint_angles)

    def runActionGroupFun(self, request, response):
        """处理运行动作组服务请求"""
        self.get_logger().info(f"Received runActionGroup request: {request}")
        runActionGroup(request.name, request.wait)
        response.success = True
        response.message = request.name
        return response

    def pub(self):
        """定时发布腿部坐标和关节状态"""
        coord = self.puppy.get_coord()
        if self.joint_state_pub_topic or self.joint_state_controller_pub_topic:
            msg = Polygon(points=[Point32(x=coord[0, i], y=coord[1, i], z=coord[2, i]) for i in range(4)])
            self.legs_coord_pub.publish(msg)

            joint_angles = self.puppy.fourLegsRelativeCoordControl(coord / 100)
            data = sum([list(joint_angles[1, :]), list(joint_angles[2, :])], [])

            joint_state_msg = JointState()
            joint_state_msg.header.stamp = self.get_clock().now().to_msg()

            for i, angle in enumerate(data):
                if i > 3:
                    angle = 0.0695044662 * angle ** 3 - 0.0249173454 * angle ** 2 - 0.786456081 * angle + 1.5443387652 - math.pi / 2

                if self.joint_state_controller_pub_topic:
                    self.joint_controller_publishers[i].publish(Float64(data=angle))

            if self.joint_state_pub_topic:
                joint_state_msg.position = data
                self.joint_state_pub.publish(joint_state_msg)

    def set_running(self, request, response):
        """处理设置运行状态服务请求"""
        self.get_logger().debug(f"Received set_running request: {request}")
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
        """处理设置自平衡服务请求"""
        self.get_logger().debug(f"Received set_self_balancing request: {request}")
        if request.data:
            self.PuppyPose = POSES['Stand'].copy()
            self.reset_stance()
            self.puppy.move_stop(servo_run_time=500)
            self.get_clock().sleep_for(Duration(seconds=0.01))
            self.puppy.servo_force_run()
            self.get_clock().sleep_for(Duration(seconds=0.5))
            self.puppy.move_stop(servo_run_time=0)
            self.puppy.imu = self.mpu
        else:
            self.puppy.imu = None
        response.success = True
        response.message = 'set_self_balancing'
        return response

    def set_mark_time(self, request, response):
        """处理设置标记时间服务请求"""
        self.get_logger().debug(f"Received set_mark_time request: {request}")
        if request.data:
            self.go_home()
            self.GaitConfig = GAIT_CONFIGS['MarkTime'].copy()
            self.puppy.gait_config(overlap_time=self.GaitConfig['overlap_time'], 
                                   swing_time=self.GaitConfig['swing_time'], 
                                   clearance_time=self.GaitConfig['clearance_time'], 
                                   z_clearance=self.GaitConfig['z_clearance'])
            self.puppy.move(x=0, y=0, yaw_rate=0)
        response.success = True
        response.message = 'set_mark_time'
        return response

    def go_home(self, request=None, response=None):
        """处理回到初始状态服务请求"""
        self.get_logger().debug('Executing go_home')
        self.PuppyPose = POSES['Stand'].copy()
        self.reset_stance()
        self.puppy.move_stop(servo_run_time=500)
        self.get_clock().sleep_for(Duration(seconds=0.01))
        self.puppy.servo_force_run()
        self.get_clock().sleep_for(Duration(seconds=0.5))
        self.puppy.move_stop(servo_run_time=0)
        if response is not None:
            response.success = True
            response.message = 'go_home'
            return response


def main(args=None):
    rclpy.init(args=args)
    try:
        puppy_node = PUPPY()
        puppy_node.get_logger().info("PUPPY node started")
        rclpy.spin(puppy_node)
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        if 'puppy_node' in locals():
            puppy_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

