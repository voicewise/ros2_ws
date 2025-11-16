#!/usr/bin/env python3
# coding=utf8
# 作者:Summer
# 邮箱:997950600@qq.com

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

from sdk.ArmMoveIK import ArmIK

# ROS节点名称
ROS_NODE_NAME = 'puppy_control'

# 导入自定义模块
sys.path.append('/home/ubuntu/software/puppypi_control')
from servo_controller import setServoPulse, updatePulse
from action_group_control import runActionGroup, stopActionGroup
from puppy_kinematics import HiwonderPuppy, PWMServoParams

class MPU6050:
    # MPU6050类，用于处理IMU数据
    def __init__(self, node):
        self.node = node
        self.data = {'accel': [0, 0, 0], 'gyro': [0, 0, 0]}
        self.second_order_filter_x = self._second_order_filter()
        self.second_order_filter_y = self._second_order_filter()
        self.subscription = self.node.create_subscription(
            Imu,
            '/ros_robot_controller/imu_raw',
            self.get_imu_callback,
            10
        )

    def get_imu_callback(self, msg):
        self.data['accel'][0] = msg.linear_acceleration.x
        self.data['accel'][1] = msg.linear_acceleration.y
        self.data['accel'][2] = msg.linear_acceleration.z
        self.data['gyro'][0] = msg.angular_velocity.x
        self.data['gyro'][1] = msg.angular_velocity.y
        self.data['gyro'][2] = msg.angular_velocity.z

    def _second_order_filter(self):
        x1 = 0
        x2 = 0
        y1 = 0
        angle = 0
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
        data = self.data
        accel_Y = math.atan2(data['accel'][0], data['accel'][2]) * 180 / math.pi
        gyro_Y = data['gyro'][1]
        angleY = self.second_order_filter_y(-accel_Y, gyro_Y, dt)

        accel_X = math.atan2(data['accel'][1], data['accel'][2]) * 180 / math.pi
        gyro_X = data['gyro'][0]
        angleX = self.second_order_filter_x(accel_X, gyro_X, dt)

        return {'pitch': -math.radians(angleX), 'roll': -math.radians(angleY), 'yaw': 0}

class PUPPY(Node):
    def __init__(self):
        super().__init__(ROS_NODE_NAME)
        # 设置 with_arm 和 offset
        self.with_arm = 0
        self.offset = 0.1 if self.with_arm else 0

        # 声明参数
        self.declare_parameter('PuppyPose.Stand.roll', math.radians(0))
        self.declare_parameter('PuppyPose.Stand.pitch', math.radians(0))
        self.declare_parameter('PuppyPose.Stand.yaw', 0.0)
        #self.declare_parameter('PuppyPose.Stand.height', -10.0)
        self.declare_parameter('PuppyPose.Stand.height', -10.0)
        #self.declare_parameter('PuppyPose.Stand.x_shift', -0.5 + self.offset)
        self.declare_parameter('PuppyPose.Stand.x_shift', -2.0)
        self.declare_parameter('PuppyPose.Stand.stance_x', 0.0)
        self.declare_parameter('PuppyPose.Stand.stance_y', 0.0)

        self.declare_parameter('PuppyPose.LieDown.roll', 0.0)
        self.declare_parameter('PuppyPose.LieDown.pitch', 0.0)
        self.declare_parameter('PuppyPose.LieDown.yaw', 0.0)
        self.declare_parameter('PuppyPose.LieDown.height', -5.0)
        self.declare_parameter('PuppyPose.LieDown.x_shift', 2.0)
        self.declare_parameter('PuppyPose.LieDown.stance_x', 0.0)
        self.declare_parameter('PuppyPose.LieDown.stance_y', 0.0)

        self.declare_parameter('PuppyPose.LookDown.roll', math.radians(0))
        self.declare_parameter('PuppyPose.LookDown.pitch', math.radians(-15))
        self.declare_parameter('PuppyPose.LookDown.yaw', 0.0)
        self.declare_parameter('PuppyPose.LookDown.height', -10.0)
        self.declare_parameter('PuppyPose.LookDown.x_shift', -0.5)
        self.declare_parameter('PuppyPose.LookDown.stance_x', 0.0)
        self.declare_parameter('PuppyPose.LookDown.stance_y', 0.0)

        self.declare_parameter('PuppyPose.LookDown_10deg.roll', math.radians(0))
        self.declare_parameter('PuppyPose.LookDown_10deg.pitch', math.radians(-10))
        self.declare_parameter('PuppyPose.LookDown_10deg.yaw', 0.0)
        self.declare_parameter('PuppyPose.LookDown_10deg.height', -9.0)
        self.declare_parameter('PuppyPose.LookDown_10deg.x_shift', -0.1)
        self.declare_parameter('PuppyPose.LookDown_10deg.stance_x', 0.0)
        self.declare_parameter('PuppyPose.LookDown_10deg.stance_y', 0.0)

        self.declare_parameter('PuppyPose.LookDown_20deg.roll', math.radians(0))
        self.declare_parameter('PuppyPose.LookDown_20deg.pitch', math.radians(-20))
        self.declare_parameter('PuppyPose.LookDown_20deg.yaw', 0.0)
        self.declare_parameter('PuppyPose.LookDown_20deg.height', -9.0)
        self.declare_parameter('PuppyPose.LookDown_20deg.x_shift', -0.1)
        self.declare_parameter('PuppyPose.LookDown_20deg.stance_x', 0.0)
        self.declare_parameter('PuppyPose.LookDown_20deg.stance_y', 0.0)

        self.declare_parameter('PuppyPose.LookDown_30deg.roll', math.radians(0))
        self.declare_parameter('PuppyPose.LookDown_30deg.pitch', math.radians(-30))
        self.declare_parameter('PuppyPose.LookDown_30deg.yaw', 0.0)
        self.declare_parameter('PuppyPose.LookDown_30deg.height', -9.6)
        self.declare_parameter('PuppyPose.LookDown_30deg.x_shift', -1.4)
        self.declare_parameter('PuppyPose.LookDown_30deg.stance_x', 1.0)
        self.declare_parameter('PuppyPose.LookDown_30deg.stance_y', 0.0)

        self.declare_parameter('PuppyPose.StandLow.roll', math.radians(0))
        self.declare_parameter('PuppyPose.StandLow.pitch', math.radians(0))
        self.declare_parameter('PuppyPose.StandLow.yaw', 0.0)
        self.declare_parameter('PuppyPose.StandLow.height', -7.0)
        self.declare_parameter('PuppyPose.StandLow.x_shift', -0.5)
        self.declare_parameter('PuppyPose.StandLow.stance_x', 0.0)
        self.declare_parameter('PuppyPose.StandLow.stance_y', 0.0)

        # 声明 GaitConfig 参数
        self.declare_parameter('GaitConfig.GaitConfigFast.overlap_time', 0.1)
        self.declare_parameter('GaitConfig.GaitConfigFast.swing_time', 0.15)
        self.declare_parameter('GaitConfig.GaitConfigFast.clearance_time', 0.0)
        self.declare_parameter('GaitConfig.GaitConfigFast.z_clearance', 5.0)

        self.declare_parameter('GaitConfig.GaitConfigSlow.overlap_time', 0.4)
        self.declare_parameter('GaitConfig.GaitConfigSlow.swing_time', 0.3)
        self.declare_parameter('GaitConfig.GaitConfigSlow.clearance_time', 0.26)
        self.declare_parameter('GaitConfig.GaitConfigSlow.z_clearance', 4.0)

        self.declare_parameter('GaitConfig.GaitConfigMarkTime.overlap_time', 0.2)
        self.declare_parameter('GaitConfig.GaitConfigMarkTime.swing_time', 0.1)
        self.declare_parameter('GaitConfig.GaitConfigMarkTime.clearance_time', 0.0)
        self.declare_parameter('GaitConfig.GaitConfigMarkTime.z_clearance', 5.0)

        # 声明其他参数
        self.declare_parameter('joint_state_pub_topic', 'false')
        self.declare_parameter('joint_state_controller_pub_topic', 'false')

        # 初始化参数
        self.init_pose_and_gait()
        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').value
        # 初始化小狗控制
        self.puppy = HiwonderPuppy(setServoPulse=setServoPulse, servoParams=PWMServoParams(), dof='8')
        self.mpu = MPU6050(self)
        self.puppy.imu = None  # 如果需要启用IMU，请设置为self.mpu

        # 初始化姿态和步态配置
        self.puppy.stance_config(
            self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
            self.PuppyPose['pitch'],
            self.PuppyPose['roll']
        )

        self.puppy.gait_config(
            overlap_time=self.GaitConfig['overlap_time'],
            swing_time=self.GaitConfig['swing_time'],
            clearance_time=self.GaitConfig['clearance_time'],
            z_clearance=self.GaitConfig['z_clearance']
        )

        # 启动小狗
        self.puppy.start()
        self.puppy.move_stop(servo_run_time=500)
        self.ak = ArmIK()
        self.ak.setPitchRangeMoving((8.51, 0, 3.3), 500)
        setServoPulse(9, 1500, 300)

        # 创建服务和订阅
        self.create_service(SetBool, '/{}/set_running'.format(ROS_NODE_NAME), self.set_running_callback)
        self.create_service(Empty, '/{}/go_home'.format(ROS_NODE_NAME), self.go_home_callback)
        self.create_service(SetBool, '/{}/set_self_balancing'.format(ROS_NODE_NAME), self.set_self_balancing_callback)
        self.create_service(SetRunActionName, '/{}/runActionGroup'.format(ROS_NODE_NAME), self.run_action_group_callback)
        self.create_service(SetBool, '/{}/set_mark_time'.format(ROS_NODE_NAME), self.set_mark_time_callback)

        self.create_subscription(Gait, '/{}/gait'.format(ROS_NODE_NAME), self.gait_callback, 10)
        self.create_subscription(Velocity, '/{}/velocity'.format(ROS_NODE_NAME), self.velocity_callback, 10)
        self.create_subscription(Velocity, '/{}/velocity_move'.format(ROS_NODE_NAME), self.velocity_move_callback, 10)
        self.create_subscription(Velocity, '/{}/velocity/autogait'.format(ROS_NODE_NAME), self.velocity_autogait_callback, 10)
        self.create_subscription(Twist, '/cmd_vel', self.cmd_vel_callback, 10)
        self.create_subscription(Twist, '/cmd_vel_nav', self.cmd_vel_nav_callback, 10)
        self.create_subscription(Pose, '/{}/pose'.format(ROS_NODE_NAME), self.pose_callback, 10)
        self.create_subscription(Polygon, '/{}/fourLegsRelativeCoordControl'.format(ROS_NODE_NAME), self.four_legs_relative_coord_control_callback, 10)
        self.create_subscription(Float32MultiArray, '/{}/gait/pc'.format(ROS_NODE_NAME), self.gait_pc_callback, 10)
        self.create_subscription(SetServo, '/{}/setServo'.format(ROS_NODE_NAME), self.set_servo_callback, 10)

        # 创建发布者
        self.legs_coord_pub = self.create_publisher(Polygon, '/{}/legs_coord'.format(ROS_NODE_NAME), 10)
        self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)
        self.joint_state = JointState()
        self.joint_state.name = ['rf_joint1', 'lf_joint1', 'rb_joint1', 'lb_joint1', 'rf_joint2', 'lf_joint2', 'rb_joint2', 'lb_joint2']

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

        # 创建定时器
        self.times = 0
        self.timer = self.create_timer(0.01, self.timer_callback)

        # 播放启动提示音
        buzzer_pub = self.create_publisher(BuzzerState, '/ros_robot_controller/set_buzzer', 10)
        buzzer_msg = BuzzerState()
        buzzer_msg.freq = 1900
        buzzer_msg.on_time = 0.1
        buzzer_msg.off_time = 0.9
        buzzer_msg.repeat = 1
        buzzer_pub.publish(buzzer_msg)

    def init_pose_and_gait(self):
        # 从参数服务器获取姿态和步态配置
        self.PuppyPose = {}

        # 获取 Stand 姿态
        self.PuppyPose['roll'] = self.get_parameter('PuppyPose.Stand.roll').value
        self.PuppyPose['pitch'] = self.get_parameter('PuppyPose.Stand.pitch').value
        self.PuppyPose['yaw'] = self.get_parameter('PuppyPose.Stand.yaw').value
        self.PuppyPose['height'] = self.get_parameter('PuppyPose.Stand.height').value
        self.PuppyPose['x_shift'] = self.get_parameter('PuppyPose.Stand.x_shift').value
        self.PuppyPose['stance_x'] = self.get_parameter('PuppyPose.Stand.stance_x').value
        self.PuppyPose['stance_y'] = self.get_parameter('PuppyPose.Stand.stance_y').value

        # 获取 GaitConfig
        self.GaitConfig = {}
        self.GaitConfig['overlap_time'] = self.get_parameter('GaitConfig.GaitConfigFast.overlap_time').value
        self.GaitConfig['swing_time'] = self.get_parameter('GaitConfig.GaitConfigFast.swing_time').value
        self.GaitConfig['clearance_time'] = self.get_parameter('GaitConfig.GaitConfigFast.clearance_time').value
        self.GaitConfig['z_clearance'] = self.get_parameter('GaitConfig.GaitConfigFast.z_clearance').value

    def stance(self, x=0.0, y=0.0, z=-11.0, x_shift=2.0):
        # 计算四足的站立位置
        return np.array([
            [x + x_shift, x + x_shift, -x + x_shift, -x + x_shift],
            [y, y, y, y],
            [z, z, z, z],
        ])

    def set_servo_callback(self, msg):
        pulse = min(max(msg.pulse, 500), 2500)
        time = min(msg.time, 30000)
        setServoPulse(msg.id, pulse, time)

    def gait_callback(self, msg):
        self.get_logger().debug('Gait Callback: %s' % msg)
        self.GaitConfig['overlap_time'] = msg.overlap_time
        self.GaitConfig['swing_time'] = msg.swing_time
        self.GaitConfig['clearance_time'] = msg.clearance_time
        self.GaitConfig['z_clearance'] = msg.z_clearance
        self.puppy.gait_config(
            overlap_time=self.GaitConfig['overlap_time'],
            swing_time=self.GaitConfig['swing_time'],
            clearance_time=self.GaitConfig['clearance_time'],
            z_clearance=self.GaitConfig['z_clearance']
        )

    def gait_pc_callback(self, msg):
        self.get_logger().debug('Gait PC Callback: %s' % msg)
        # data:[params.gait, params.height, params.period, params.x, params.y, params.yaw]
        if msg.data[0] == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )
        else:
            # 根据步态参数调整步态配置
            if msg.data[0] == 1:  # Trot
                overlap_time = msg.data[2] / 4
                swing_time = msg.data[2] / 4
                clearance_time = 0
            elif msg.data[0] == 2:  # Amble
                overlap_time = msg.data[2] / 5
                swing_time = msg.data[2] / 5
                clearance_time = msg.data[2] / 10
            elif msg.data[0] == 3:  # Walk
                overlap_time = msg.data[2] / 6
                swing_time = msg.data[2] / 6
                clearance_time = msg.data[2] / 6

            self.GaitConfig['overlap_time'] = overlap_time
            self.GaitConfig['swing_time'] = swing_time
            self.GaitConfig['clearance_time'] = clearance_time
            self.GaitConfig['z_clearance'] = msg.data[1]

            self.puppy.gait_config(
                overlap_time=self.GaitConfig['overlap_time'],
                swing_time=self.GaitConfig['swing_time'],
                clearance_time=self.GaitConfig['clearance_time'],
                z_clearance=self.GaitConfig['z_clearance']
            )
            self.velocity_callback(Velocity(x=msg.data[3], y=msg.data[4], yaw_rate=msg.data[5]))

    def cmd_vel_callback(self, msg):
        self.get_logger().debug('Cmd Vel Callback: %s' % msg)
        if abs(msg.linear.x) > 0.5 or abs(msg.angular.z) > 0.5:
            # 更新姿态为 LieDown
            self.update_puppy_pose('LieDown')
            if abs(msg.linear.x) > abs(msg.angular.z):
                self.velocity_callback(Velocity(16 * np.sign(msg.linear.x), 0, 0))
            else:
                self.velocity_callback(Velocity(0, 0, np.radians(25) * np.sign(msg.angular.z)))
        elif msg.linear.x == 0 and msg.angular.z == 0:
            self.velocity_callback(Velocity(0, 0, 0))

    def cmd_vel_nav_callback(self, msg):
        self.get_logger().debug('Cmd Vel Nav Callback: %s' % msg)
        self.update_puppy_pose('LieDown')
        self.velocity_callback(Velocity(msg.linear.x * 100, 0, msg.angular.z))

    def velocity_move_callback(self, msg):
        self.get_logger().debug('Velocity Move Callback: %s' % msg)
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )
        else:
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_callback(self, msg):
        self.get_logger().debug('Velocity Callback: %s' % msg)
        if msg.x == -999:  # 原地踏步
            self.puppy.move(x=0.0, y=0.0, yaw_rate=0.0)
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )
        elif msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            if msg.x > 0:
                self.puppy.stance_config(
                    self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift'] - 0.8),
                    self.PuppyPose['pitch'],
                    self.PuppyPose['roll']
                )
            else:
                self.puppy.stance_config(
                    self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift'] + 0.8),
                    self.PuppyPose['pitch'],
                    self.PuppyPose['roll']
                )
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_autogait_callback(self, msg):
        self.get_logger().debug('Velocity Autogait Callback: %s' % msg)
        if msg.x == 0 and msg.y == 0 and msg.yaw_rate == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )
        elif abs(msg.x) <= 35 and abs(msg.y) == 0 and abs(msg.yaw_rate) <= np.radians(51):
            # 根据速度调整步态参数
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

            self.GaitConfig['overlap_time'] = min(overlap_time_x, overlap_time_yaw_rate)
            self.GaitConfig['swing_time'] = min(swing_time_x, swing_time_yaw_rate)
            self.GaitConfig['clearance_time'] = min(clearance_time_x, clearance_time_yaw_rate)

            self.puppy.gait_config(
                overlap_time=self.GaitConfig['overlap_time'],
                swing_time=self.GaitConfig['swing_time'],
                clearance_time=self.GaitConfig['clearance_time'],
                z_clearance=self.GaitConfig['z_clearance']
            )

            if msg.x > 0:
                self.puppy.stance_config(
                    self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift'] - 0.8),
                    self.PuppyPose['pitch'],
                    self.PuppyPose['roll']
                )
            else:
                self.puppy.stance_config(
                    self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift'] + 0.8),
                    self.PuppyPose['pitch'],
                    self.PuppyPose['roll']
                )
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def pose_callback(self, msg):
        self.get_logger().debug('Pose Callback: %s' % msg)
        if (abs(msg.roll) <= math.radians(31) and abs(msg.pitch) <= math.radians(31)
                and abs(msg.yaw) == 0 and -15 <= msg.height <= -5
                and abs(msg.stance_x) <= 5 and abs(msg.stance_y) <= 5
                and abs(msg.x_shift) <= 10):
            if msg.run_time != 0:
                self.puppy.move_stop(servo_run_time=msg.run_time)
                self.puppy.servo_force_run()
            self.PuppyPose = {
                'roll': msg.roll,
                'pitch': msg.pitch,
                'yaw': msg.yaw,
                'height': msg.height,
                'x_shift': msg.x_shift,
                'stance_x': msg.stance_x,
                'stance_y': msg.stance_y
            }
            self.puppy.stance_config(
                self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
                self.PuppyPose['pitch'],
                self.PuppyPose['roll']
            )

    def four_legs_relative_coord_control_callback(self, msg):
        self.get_logger().debug('Four Legs Relative Coord Control Callback: %s' % msg)
        rotated_foot_locations = np.zeros((3, 4))
        for idx, p in enumerate(msg.points):
            rotated_foot_locations[:, idx] = [p.x, p.y, p.z]
        joint_angles = self.puppy.fourLegsRelativeCoordControl(rotated_foot_locations)
        self.puppy.sendServoAngle(joint_angles)

    def run_action_group_callback(self, request, response):
        self.get_logger().debug('Run Action Group Callback: %s' % request)
        runActionGroup(request.name, request.wait)
        response.success = True
        response.message = request.name
        return response

    def set_running_callback(self, request, response):
        self.get_logger().debug('Set Running Callback: %s' % request)
        if request.data:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.start()
        else:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.end()
        response.success = True
        response.message = 'set_running'
        return response

    def set_self_balancing_callback(self, request, response):
        self.get_logger().debug('Set Self Balancing Callback: %s' % request)
        if request.data:
            self.update_puppy_pose('LieDown')
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.servo_force_run()
            self.puppy.move_stop(servo_run_time=0)
            self.puppy.imu = self.mpu
        else:
            self.puppy.imu = None
        response.success = True
        response.message = 'set_self_balancing'
        return response

    def set_mark_time_callback(self, request, response):
        self.get_logger().debug('Set Mark Time Callback: %s' % request)
        if request.data:
            self.go_home_callback(None, None)
            self.GaitConfig = {
                'overlap_time': self.get_parameter('GaitConfig.GaitConfigMarkTime.overlap_time').value,
                'swing_time': self.get_parameter('GaitConfig.GaitConfigMarkTime.swing_time').value,
                'clearance_time': self.get_parameter('GaitConfig.GaitConfigMarkTime.clearance_time').value,
                'z_clearance': self.get_parameter('GaitConfig.GaitConfigMarkTime.z_clearance').value
            }
            self.puppy.gait_config(
                overlap_time=self.GaitConfig['overlap_time'],
                swing_time=self.GaitConfig['swing_time'],
                clearance_time=self.GaitConfig['clearance_time'],
                z_clearance=self.GaitConfig['z_clearance']
            )
            self.puppy.move(x=0, y=0, yaw_rate=0)
        response.success = True
        response.message = 'set_mark_time'
        return response

    def go_home_callback(self, request, response):
        self.get_logger().debug('Go Home Callback')
        self.update_puppy_pose('LieDown')
        self.puppy.move_stop(servo_run_time=500)
        self.puppy.servo_force_run()
        self.puppy.move_stop(servo_run_time=0)
        if response is not None:
            return response

    def update_puppy_pose(self, pose_name):
        # 更新小狗姿态
        self.PuppyPose['roll'] = self.get_parameter('PuppyPose.{}.roll'.format(pose_name)).value
        self.PuppyPose['pitch'] = self.get_parameter('PuppyPose.{}.pitch'.format(pose_name)).value
        self.PuppyPose['yaw'] = self.get_parameter('PuppyPose.{}.yaw'.format(pose_name)).value
        self.PuppyPose['height'] = self.get_parameter('PuppyPose.{}.height'.format(pose_name)).value
        self.PuppyPose['x_shift'] = self.get_parameter('PuppyPose.{}.x_shift'.format(pose_name)).value
        self.PuppyPose['stance_x'] = self.get_parameter('PuppyPose.{}.stance_x'.format(pose_name)).value
        self.PuppyPose['stance_y'] = self.get_parameter('PuppyPose.{}.stance_y'.format(pose_name)).value
        self.puppy.stance_config(
            self.stance(self.PuppyPose['stance_x'], self.PuppyPose['stance_y'], self.PuppyPose['height'], self.PuppyPose['x_shift']),
            self.PuppyPose['pitch'],
            self.PuppyPose['roll']
        )

    def timer_callback(self):
        self.times += 1
        if self.times >= 100:
            self.times = 0
            coord = self.puppy.get_coord()
            msg = Polygon()
            for i in range(4):
                point = Point32()
                point.x = coord[0, i]
                point.y = coord[1, i]
                point.z = coord[2, i]
                msg.points.append(point)
            self.legs_coord_pub.publish(msg)
            self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').value
            self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').value

        if self.joint_state_pub_topic or self.joint_state_controller_pub_topic:
            coord = self.puppy.get_coord()
            joint_angles = self.puppy.fourLegsRelativeCoordControl(coord / 100)
            data = sum([list(joint_angles[1, :]), list(joint_angles[2, :])], [])
            self.joint_state.header.stamp = self.get_clock().now().to_msg()
            for i in range(len(data)):
                if i > 3:
                    data[i] = 0.0695044662 * data[i] ** 3 - 0.0249173454 * data[i] ** 2 - 0.786456081 * data[i] + 1.5443387652 - 3.1415926 / 2
                if self.joint_state_controller_pub_topic:
                    msg = Float64()
                    msg.data = data[i]
                    self.joint_controller_publishers[i].publish(msg)
            if self.joint_state_pub_topic:
                self.joint_state.position = data
                self.joint_state_pub.publish(self.joint_state)

def main(args=None):
    rclpy.init(args=args)
    puppy_node = PUPPY()
    try:
        rclpy.spin(puppy_node)
    except KeyboardInterrupt:
        pass
    finally:
        puppy_node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
