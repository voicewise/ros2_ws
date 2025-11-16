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
from sdk.ArmMoveIK import *
sys.path.append('/home/ubuntu/software/puppypi_control')
from servo_controller import setServoPulse, updatePulse
from action_group_control import runActionGroup, stopActionGroup
from puppy_kinematics import HiwonderPuppy, PWMServoParams
import yaml  # 添加这一行
from std_msgs.msg import Float64  
from ros_robot_controller_sdk import Board
from pwm_servo_control import PWMServoControl

class MPU6050:
    def __init__(self, node):
        # 订阅IMU数据
        node.create_subscription(Imu, '/ros_robot_controller/imu_raw', self.get_imu_data, 10)
        self.data = {'accel': [0, 0, 0], 'gyro': [0, 0, 0]}
        self.second_order_filter_x = self._second_order_filter()
        self.second_order_filter_y = self._second_order_filter()

    def get_imu_data(self, msg):
        # 更新加速度和陀螺仪数据
        self.data['accel'][0] = msg.linear_acceleration.x
        self.data['accel'][1] = msg.linear_acceleration.y
        self.data['accel'][2] = msg.linear_acceleration.z
        self.data['gyro'][0] = msg.angular_velocity.x
        self.data['gyro'][1] = msg.angular_velocity.y
        self.data['gyro'][2] = msg.angular_velocity.z

    def _second_order_filter(self):
        # 二阶滤波器参数
        x1 = 0
        x2 = 0
        y1 = 0
        angle = 0
        K2 = 0.02

        def filter_func(angle_m, gyro_m, dt=0.01):
            nonlocal x1, x2, y1, angle, K2
            x1 = (angle_m - angle) * (1 - K2) * (1 - K2)
            y1 += x1 * dt
            x2 = y1 + 2 * (1 - K2) * (angle_m - angle) + gyro_m
            angle += x2 * dt
            return angle

        return filter_func

    def get_euler_angle(self, dt=0.01):
        # 计算欧拉角
        accel_y = math.atan2(self.data['accel'][0], self.data['accel'][2]) * 180 / math.pi
        gyro_y = self.data['gyro'][1]
        angle_y = self.second_order_filter_y(-accel_y, gyro_y, dt)

        accel_x = math.atan2(self.data['accel'][1], self.data['accel'][2]) * 180 / math.pi
        gyro_x = self.data['gyro'][0]
        angle_x = self.second_order_filter_x(accel_x, gyro_x, dt)

        return {'pitch': -math.radians(angle_x), 'roll': -math.radians(angle_y), 'yaw': 0.0}

class PuppyControl(Node):
    def __init__(self):
        super().__init__('puppy_control')

        # 声明参数
        self.declare_parameters(
            namespace='',
            parameters=[
                ('joint_state_pub_topic', False),
                ('joint_state_controller_pub_topic', False),
                ('config_file', '/home/ubuntu/ros2_ws/src/driver/puppy_control/config/puppy_params.yaml'),
            ]
        )

        # 获取参数值
        self.joint_state_pub_topic = self.get_parameter('joint_state_pub_topic').get_parameter_value().bool_value
        self.joint_state_controller_pub_topic = self.get_parameter('joint_state_controller_pub_topic').get_parameter_value().bool_value
        config_path = self.get_parameter('config_file').get_parameter_value().string_value

        # 加载YAML配置文件
        self.load_parameters(config_path)

        # 初始化实例变量
        self.puppy_pose = self.StanceConfig.get('LieDown', {}).copy()
        self.gait_config = self.GaitConfig.get('GaitConfigFast', {}).copy()
        self.ak = ArmIK()
        self.cooldown = False

        # 添加调试日志，确认参数是否正确加载
        self.get_logger().info(f"Puppy Pose Loaded: {self.puppy_pose}")
        self.get_logger().info(f"Gait Config Loaded: {self.gait_config}")

        # 初始化Puppy
        self.puppy = HiwonderPuppy(setServoPulse=setServoPulse, servoParams=PWMServoParams(), dof='8')
        self.puppy.imu = None  # 将IMU对象赋值给puppy.imu

        # 创建并初始化IMU对象
        self.mpu6050 = MPU6050(self)
        self.puppy.imu = self.mpu6050

        # 设置初始姿态和步态
        self.puppy.stance_config(
            self.stance(
                self.puppy_pose['stance_x'],
                self.puppy_pose['stance_y'],
                self.puppy_pose['height'],
                self.puppy_pose['x_shift']
            ),
            self.puppy_pose['pitch'],
            self.puppy_pose['roll']
        )

        self.puppy.gait_config(
            overlap_time=self.gait_config['overlap_time'],
            swing_time=self.gait_config['swing_time'],
            clearance_time=self.gait_config['clearance_time'],
            z_clearance=self.gait_config['z_clearance']
        )

        # 启动puppy
        self.puppy.start()
        self.puppy.move_stop(servo_run_time=500)
        self.ak.setPitchRangeMoving((8.51, 0, 3.3), 500)
        time.sleep(0.5)
        setServoPulse(9, 1500, 300)
        time.sleep(0.3)

        # 创建服务
        self.create_service(SetBool, f'/{self.get_name()}/set_running', self.set_running)
        self.create_service(Empty, f'/{self.get_name()}/go_home', self.go_home)
        self.create_service(SetBool, f'/{self.get_name()}/set_self_balancing', self.set_self_balancing)
        self.create_service(SetRunActionName, f'/{self.get_name()}/runActionGroup', self.run_action_group_callback)
        self.create_service(SetBool, f'/{self.get_name()}/set_mark_time', self.set_mark_time)

        # 创建订阅者
        self.create_subscription(Gait, f'/{self.get_name()}/gait', self.gait_callback, 10)
        self.create_subscription(Velocity, f'/{self.get_name()}/velocity', self.velocity_callback, 10)
        self.create_subscription(Velocity, f'/{self.get_name()}/velocity_move', self.velocity_move_callback, 10)
        self.create_subscription(Velocity, f'/{self.get_name()}/velocity/autogait', self.velocity_autogait_callback, 10)
        self.create_subscription(Twist, '/cmd_vel', self.cmd_vel_callback, 10)
        self.create_subscription(Twist, '/cmd_vel_nav', self.cmd_vel_nav_callback, 10)
        self.create_subscription(Pose, f'/{self.get_name()}/pose', self.pose_callback, 10)
        self.create_subscription(Polygon, f'/{self.get_name()}/fourLegsRelativeCoordControl', self.four_legs_relative_coord_control_callback, 10)
        self.create_subscription(Float32MultiArray, f'/{self.get_name()}/gait/pc', self.gait_pc_callback, 10)
        self.create_subscription(SetServo, f'/{self.get_name()}/setServo', self.set_servo_callback, 10)

        # 创建发布者
        self.legs_coord_pub = self.create_publisher(Polygon, f'/{self.get_name()}/legs_coord', 10)
        self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)
        self.pose_pub = self.create_publisher(Pose, f'/{self.get_name()}/pose', 10)  # 移动Pose发布者到__init__

        # 初始化JointState消息
        self.joint_state = JointState()
        self.joint_state.name = ['rf_joint1', 'lf_joint1', 'rb_joint1', 'lb_joint1',
                                 'rf_joint2', 'lf_joint2', 'rb_joint2', 'lb_joint2']
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
        self.joint_controller_publishers = [
            self.create_publisher(Float64, topic, 10) for topic in command_topics
        ]

        # 初始化Buzzer
        self.buzzer_pub = self.create_publisher(BuzzerState, '/ros_robot_controller/set_buzzer', 10)
        self.publish_buzzer()

        # 创建定时器用于发布关节状态
        self.timer_pub = self.create_timer(0.01, self.publish_joint_states)  # 100Hz

        self.get_logger().info(f'{self.get_name()} 节点已启动。')

    def load_parameters(self, config_path):
        """
        从YAML文件加载参数。
        """
        try:
            with open(config_path, 'r') as file:
                config = yaml.safe_load(file)
                node_name = self.get_name().lstrip('/')  # 获取节点名称，去除前导 '/'
                ros_params = config.get(node_name, {}).get('ros__parameters', {})
                self.StanceConfig = ros_params.get('stance', {})
                self.GaitConfig = ros_params.get('gait_config', {})
                self.joint_state_pub_topic = ros_params.get('joint_state_pub_topic', False)
                self.joint_state_controller_pub_topic = ros_params.get('joint_state_controller_pub_topic', False)
            
            # 添加调试日志，确认参数是否正确加载
            self.get_logger().info(f"Loaded StanceConfig: {self.StanceConfig}")
            self.get_logger().info(f"Loaded GaitConfig: {self.GaitConfig}")
            self.get_logger().info(f"joint_state_pub_topic: {self.joint_state_pub_topic}")
            self.get_logger().info(f"joint_state_controller_pub_topic: {self.joint_state_controller_pub_topic}")
            
            self.get_logger().info('YAML参数加载成功。')
        except Exception as e:
            self.get_logger().error(f'加载YAML配置失败: {e}')
            self.StanceConfig = {}
            self.GaitConfig = {}

    def stance(self, x=0, y=0, z=-11, x_shift=2):
        """
        生成姿态配置。
        """
        return np.array([
            [x + x_shift, x + x_shift, -x + x_shift, -x + x_shift],
            [y, y, y, y],
            [z, z, z, z],
        ])

    def publish_buzzer(self):
        """
        发布蜂鸣器状态。
        """
        msg = BuzzerState()
        msg.freq = 1900
        msg.on_time = 0.1
        msg.off_time = 0.9
        msg.repeat = 1
        self.buzzer_pub.publish(msg)
        self.get_logger().info('发布蜂鸣器状态。')

    def publish_joint_states(self):
        self.get_logger().debug('Publishing joint states...')
        coord = self.puppy.get_coord()
        if coord is None:
            self.get_logger().warn('No coordinate data available.')
            return

        joint_angles = self.puppy.fourLegsRelativeCoordControl(coord / 100.0)
        data = list(joint_angles[1, :]) + list(joint_angles[2, :])

        for i in range(len(data)):
            if i > 3:
                data[i] = 0.0695044662 * data[i]**3 - 0.0249173454 * data[i]**2 - 0.786456081 * data[i] + 1.5443387652 - math.pi / 2

            if self.joint_state_controller_pub_topic:
                # 使用正确的关键字参数形式构造 Float64 消息
                self.joint_controller_publishers[i].publish(Float64(data=data[i]))
                self.get_logger().debug(f'Published joint {i} with value {data[i]}')

        if self.joint_state_pub_topic:
            self.joint_state.header.stamp = self.get_clock().now().to_msg()
            self.joint_state.position = data
            self.joint_state_pub.publish(self.joint_state)
            self.get_logger().debug('Published joint states to /joint_states')

    def run_action_group_callback(self, request, response):
        """
        处理runActionGroup服务的回调。
        """
        self.get_logger().debug(f'Received runActionGroup request: {request.name}, wait: {request.wait}')
        try:
            runActionGroup(request.name, request.wait)
            response.success = True
            response.message = f"执行动作组: {request.name}"
            self.get_logger().info(response.message)

            # 更新姿态（根据实际需求）
            # 假设动作组执行后，姿态应更新为某个预定义姿态
            # 这里以'LieDown'为例
            if 'LieDown' in self.StanceConfig:
                self.puppy_pose = self.StanceConfig['LieDown'].copy()
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift']
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )

                # 发布Pose消息
                pose_msg = Pose()
                pose_msg.roll = self.puppy_pose['roll']
                pose_msg.pitch = self.puppy_pose['pitch']
                pose_msg.yaw = self.puppy_pose['yaw']
                pose_msg.height = self.puppy_pose['height']
                pose_msg.x_shift = self.puppy_pose['x_shift']
                pose_msg.stance_x = self.puppy_pose['stance_x']
                pose_msg.stance_y = self.puppy_pose['stance_y']
                self.pose_pub.publish(pose_msg)  # 使用已有的Pose发布者

        except Exception as e:
            response.success = False
            response.message = f"执行动作组失败: {e}"
            self.get_logger().error(response.message)
        return response

    def set_running(self, request, response):
        """
        设置机器人运行状态的服务回调。
        """
        self.get_logger().debug(f'Received set_running request: {request.data}')
        if request.data:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.start()
            response.success = True
            response.message = '机器人开始运行。'
        else:
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.end()
            response.success = True
            response.message = '机器人停止运行。'
        self.get_logger().info(response.message)
        return response

    def go_home(self, request, response):
        """
        使机器人回到家中的服务回调。
        """
        self.get_logger().info('执行回家动作。')
        self.puppy_pose = self.StanceConfig.get('Stand', {}).copy()
        self.puppy.stance_config(
            self.stance(
                self.puppy_pose['stance_x'],
                self.puppy_pose['stance_y'],
                self.puppy_pose['height'],
                self.puppy_pose['x_shift']
            ),
            self.puppy_pose['pitch'],
            self.puppy_pose['roll']
        )
        self.puppy.move_stop(servo_run_time=500)
        self.puppy.servo_force_run()
        time.sleep(0.5)
        self.puppy.move_stop(servo_run_time=0)
        return response

    def set_self_balancing(self, request, response):
        """
        设置机器人自平衡的服务回调。
        """
        self.get_logger().debug(f'Received set_self_balancing request: {request.data}')
        if request.data:
            self.puppy_pose = self.StanceConfig.get('Stand', {}).copy()
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
            self.puppy.move_stop(servo_run_time=500)
            self.puppy.servo_force_run()
            time.sleep(0.5)
            self.puppy.move_stop(servo_run_time=0)
            self.puppy.imu = self.mpu6050
            response.success = True
            response.message = '启用自平衡。'
        else:
            self.puppy.imu = None
            response.success = True
            response.message = '禁用自平衡。'
        self.get_logger().info(response.message)
        return response

    def set_mark_time(self, request, response):
        """
        设置标记时间的服务回调。
        """
        self.get_logger().debug(f'Received set_mark_time request: {request.data}')
        if request.data:
            self.go_home(request, response)
            self.gait_config = self.GaitConfig.get('GaitConfigMarkTime', {}).copy()
            self.puppy.gait_config(
                overlap_time=self.gait_config['overlap_time'],
                swing_time=self.gait_config['swing_time'],
                clearance_time=self.gait_config['clearance_time'],
                z_clearance=self.gait_config['z_clearance']
            )
            self.puppy.move(x=0.0, y=0.0, yaw_rate=0.0)
            response.success = True
            response.message = '设置标记时间。'
        else:
            response.success = False
            response.message = '取消设置标记时间。'
        self.get_logger().info(response.message)
        return response

    def gait_callback(self, msg):
        """
        处理Gait消息的回调。
        """
        self.get_logger().debug(f'Received Gait message: {msg}')
        self.gait_config = {
            'overlap_time': msg.overlap_time,
            'swing_time': msg.swing_time,
            'clearance_time': msg.clearance_time,
            'z_clearance': msg.z_clearance
        }
        self.puppy.gait_config(
            overlap_time=self.gait_config['overlap_time'],
            swing_time=self.gait_config['swing_time'],
            clearance_time=self.gait_config['clearance_time'],
            z_clearance=self.gait_config['z_clearance']
        )

    def gait_pc_callback(self, msg):
        """
        处理Gait PC消息的回调。
        """
        self.get_logger().debug(f'Received Gait PC message: {msg}')
        if len(msg.data) < 6:
            self.get_logger().warn('Gait PC message data不足。')
            return

        gait_type = int(msg.data[0])
        z_clearance = float(msg.data[1])
        period = float(msg.data[2])
        x = float(msg.data[3])
        y = float(msg.data[4])
        yaw_rate = float(msg.data[5])

        if gait_type == 0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
        else:
            if gait_type == 1:  # Trot
                overlap_time_x = period / 4
                swing_time_x = period / 4
                clearance_time_x = 0.0
            elif gait_type == 2:  # Amble
                overlap_time_x = period / 5
                swing_time_x = period / 5
                clearance_time_x = period / 10
            elif gait_type == 3:  # Walk
                overlap_time_x = period / 6
                swing_time_x = period / 6
                clearance_time_x = period / 6

            if abs(yaw_rate) <= math.radians(10):
                overlap_time_yaw = 0.23 - abs(yaw_rate) * 0.37
                swing_time_yaw = 0.36 - abs(yaw_rate) * 0.74
                clearance_time_yaw = swing_time_yaw - 0.04
            elif abs(yaw_rate) <= math.radians(20):
                overlap_time_yaw = 0.23 - abs(yaw_rate) * 0.37
                swing_time_yaw = 0.41 - abs(yaw_rate) * 0.74
                clearance_time_yaw = 0.0
            else:
                overlap_time_yaw = 0.1
                swing_time_yaw = 0.15
                clearance_time_yaw = 0.0

            self.gait_config['overlap_time'] = min(overlap_time_x, overlap_time_yaw)
            self.gait_config['swing_time'] = min(swing_time_x, swing_time_yaw)
            self.gait_config['clearance_time'] = min(clearance_time_x, clearance_time_yaw)

            self.gait_config['z_clearance'] = z_clearance
            self.puppy.gait_config(
                overlap_time=self.gait_config['overlap_time'],
                swing_time=self.gait_config['swing_time'],
                clearance_time=self.gait_config['clearance_time'],
                z_clearance=self.gait_config['z_clearance']
            )

            if x > 0.0:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] - 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )
            else:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] + 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )

            self.puppy.move(x=x, y=y, yaw_rate=yaw_rate)

    def velocity_callback(self, msg):
        """
        处理Velocity消息的回调。
        """
        self.get_logger().debug(f'Received Velocity message: {msg}')
        if msg.x == -999:  # 原地踏步
            self.puppy.move(x=0.0, y=0.0, yaw_rate=0.0)
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
        elif msg.x == 0.0 and msg.y == 0.0 and msg.yaw_rate == 0.0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
        elif abs(msg.x) <= 35.0 and msg.y == 0.0 and abs(msg.yaw_rate) <= math.radians(51):
            if msg.x > 0:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] - 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )
            else:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] + 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_move_callback(self, msg):
        """
        处理velocity_move消息的回调。
        """
        self.get_logger().debug(f'Received velocity_move message: {msg}')
        if msg.x == 0.0 and msg.y == 0.0 and msg.yaw_rate == 0.0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
        else:
            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def velocity_autogait_callback(self, msg):
        """
        处理velocity_autogait消息的回调。
        """
        self.get_logger().debug(f'Received velocity_autogait message: {msg}')
        if msg.x == 0.0 and msg.y == 0.0 and msg.yaw_rate == 0.0:
            self.puppy.move_stop(servo_run_time=100)
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )
        elif abs(msg.x) <= 35.0 and msg.y == 0.0 and abs(msg.yaw_rate) <= math.radians(51):
            # 根据x和yaw_rate调整步态配置
            if abs(msg.x) <= 10.0:
                overlap_time_x = 0.45 - abs(msg.x) * 0.023
                swing_time_x = 0.38 - abs(msg.x) * 0.0154
                clearance_time_x = swing_time_x - 0.04
            elif abs(msg.x) <= 15.0:
                overlap_time_x = 0.45 - abs(msg.x) * 0.023
                swing_time_x = 0.38 - abs(msg.x) * 0.0154
                clearance_time_x = 0.0
            else:
                overlap_time_x = 0.1
                swing_time_x = 0.15
                clearance_time_x = 0.0

            if abs(msg.yaw_rate) <= math.radians(10):
                overlap_time_yaw = 0.23 - abs(msg.yaw_rate) * 0.37
                swing_time_yaw = 0.36 - abs(msg.yaw_rate) * 0.74
                clearance_time_yaw = swing_time_yaw - 0.04
            elif abs(msg.yaw_rate) <= math.radians(20):
                overlap_time_yaw = 0.23 - abs(msg.yaw_rate) * 0.37
                swing_time_yaw = 0.41 - abs(msg.yaw_rate) * 0.74
                clearance_time_yaw = 0.0
            else:
                overlap_time_yaw = 0.1
                swing_time_yaw = 0.15
                clearance_time_yaw = 0.0

            self.gait_config['overlap_time'] = min(overlap_time_x, overlap_time_yaw)
            self.gait_config['swing_time'] = min(swing_time_x, swing_time_yaw)
            self.gait_config['clearance_time'] = min(clearance_time_x, clearance_time_yaw)

            self.gait_config['z_clearance'] = msg.z_clearance
            self.puppy.gait_config(
                overlap_time=self.gait_config['overlap_time'],
                swing_time=self.gait_config['swing_time'],
                clearance_time=self.gait_config['clearance_time'],
                z_clearance=self.gait_config['z_clearance']
            )

            if msg.x > 0.0:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] - 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )
            else:
                self.puppy.stance_config(
                    self.stance(
                        self.puppy_pose['stance_x'],
                        self.puppy_pose['stance_y'],
                        self.puppy_pose['height'],
                        self.puppy_pose['x_shift'] + 0.8
                    ),
                    self.puppy_pose['pitch'],
                    self.puppy_pose['roll']
                )

            self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

    def cmd_vel_callback(self, msg):
        """
        处理cmd_vel消息的回调。
        """
        self.get_logger().debug(f'Received cmd_vel message: {msg}')
        if abs(msg.linear.x) > 0.5 or abs(msg.angular.z) > 0.5:
            self.puppy_pose = self.StanceConfig['Stand'].copy()
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )

            if abs(msg.linear.x) > abs(msg.angular.z):
                self.velocity_publish(Velocity(x=16 * np.sign(msg.linear.x), y=0.0, yaw_rate=0.0))
            else:
                self.velocity_publish(Velocity(x=0.0, y=0.0, yaw_rate=math.radians(25) * np.sign(msg.angular.z)))
        elif msg.linear.x == 0.0 and msg.angular.z == 0.0:
            self.velocity_publish(Velocity(x=0.0, y=0.0, yaw_rate=0.0))

    def cmd_vel_nav_callback(self, msg):
        """
        处理cmd_vel_nav消息的回调。
        """
        self.get_logger().debug(f'Received cmd_vel_nav message: {msg}')
        self.puppy_pose = self.StanceConfig['Stand'].copy()
        self.puppy.stance_config(
            self.stance(
                self.puppy_pose['stance_x'],
                self.puppy_pose['stance_y'],
                self.puppy_pose['height'],
                self.puppy_pose['x_shift']
            ),
            self.puppy_pose['pitch'],
            self.puppy_pose['roll']
        )
        self.velocity_publish(Velocity(x=msg.linear.x * 100.0, y=0.0, yaw_rate=msg.angular.z))

    def pose_callback(self, msg):
        """
        处理Pose消息的回调。
        """
        self.get_logger().debug(f'Received Pose message: {msg}')
        # 验证Pose参数
        if (abs(msg.roll) <= math.radians(31) and abs(msg.pitch) <= math.radians(31) and
            abs(msg.yaw) == 0.0 and -15.0 <= msg.height <= -5.0 and
            abs(msg.stance_x) <= 5.0 and abs(msg.stance_y) <= 5.0 and
            abs(msg.x_shift) <= 10.0):

            if hasattr(msg, 'run_time') and msg.run_time != 0:
                self.puppy.move_stop(servo_run_time=msg.run_time)
                self.puppy.servo_force_run()
                time.sleep(0.01)

            self.puppy_pose = {
                'roll': msg.roll,
                'pitch': msg.pitch,
                'yaw': msg.yaw,
                'height': msg.height,
                'x_shift': msg.x_shift,
                'stance_x': msg.stance_x,
                'stance_y': msg.stance_y
            }
            self.puppy.stance_config(
                self.stance(
                    self.puppy_pose['stance_x'],
                    self.puppy_pose['stance_y'],
                    self.puppy_pose['height'],
                    self.puppy_pose['x_shift']
                ),
                self.puppy_pose['pitch'],
                self.puppy_pose['roll']
            )

    def four_legs_relative_coord_control_callback(self, msg):
        """
        处理四腿相对坐标控制的回调。
        """
        self.get_logger().debug(f'Received fourLegsRelativeCoordControl message: {msg}')
        rotated_foot_locations = np.zeros((3, 4))
        for idx, p in enumerate(msg.points):
            rotated_foot_locations[:, idx] = [p.x, p.y, p.z]

        joint_angles = self.puppy.fourLegsRelativeCoordControl(rotated_foot_locations)
        self.puppy.sendServoAngle(joint_angles)

    def set_servo_callback(self, msg):
        """
        处理SetServo消息的回调。
        """
        # 限制脉冲宽度和时间范围
        if msg.pulse > 2500:
            msg.pulse = 2500
        if msg.pulse < 500:
            msg.pulse = 500
        if msg.time > 30000:
            msg.time = 30000

        setServoPulse(msg.id, msg.pulse, msg.time)

    def velocity_publish(self, msg):
        """
        发布Velocity消息。
        """
        self.puppy.move(x=msg.x, y=msg.y, yaw_rate=msg.yaw_rate)

def main(args=None):
    rclpy.init(args=args)
    node = PuppyControl()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('接收到键盘中断信号，正在关闭节点...')
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
