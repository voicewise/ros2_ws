#!/usr/bin/env python3
# coding=utf8
# Date:2024/04/27
# Author:hiwonder

import math
import time
import rclpy
from rclpy.node import Node
from rclpy.duration import Duration
from threading import Timer, RLock
import numpy as np
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
from std_srvs.srv import SetBool, Trigger
from puppy_control_msgs.srv import SetInt64, SetFloat64List

MAX_SCAN_ANGLE = 360  # 激光的扫描角度 (the scanning angle of the laser)

class LidarController(Node):
    def __init__(self):
        super().__init__('lidar_app')
        
        # 初始化参数
        self.running_mode = 0  # 1: 雷达避障模式 2: 雷达警卫模式 3: 警卫看守模式
        self.threshold = 0.3  # meters 距离阈值 (distance threshold)
        self.scan_angle = math.radians(90)  # radians 向前的扫描角度 (the forward scanning angle)
        self.speed = 0.12  # 单位米，避障模式的速度 (speed in meters per second for obstacle avoidance mode)
        self.timestamp = 0
        self.lock = RLock()
        self.lidar_sub = None
        self.heartbeat_timer = None

        # 创建Publisher
        self.velocity_pub = self.create_publisher(Twist, '/cmd_vel_nav', 10)
        # 初始化发布一个空的Twist消息
        self.velocity_pub.publish(Twist())

        # 创建服务
        self.enter_srv = self.create_service(Trigger, '/lidar_app/enter', self.enter_func)
        self.exit_srv = self.create_service(Trigger, '/lidar_app/exit', self.exit_func)
        self.heartbeat_srv = self.create_service(SetBool, '/lidar_app/heartbeat', self.heartbeat_srv_cb)
        self.set_running_srv = self.create_service(SetInt64, "/lidar_app/set_running", self.set_running_srv_callback)
        self.set_parameters_srv = self.create_service(SetFloat64List, "/lidar_app/adjust_parameters", self.set_parameters_srv_callback)

        self.get_logger().info("LidarController node has been initialized.")

    def reset_value(self):
        with self.lock:
            self.running_mode = 0
            self.threshold = 0.3
            self.speed = 0.12
            self.scan_angle = math.radians(90)

            if self.lidar_sub is not None:
                self.destroy_subscription(self.lidar_sub)
                self.lidar_sub = None

            if self.heartbeat_timer:
                self.heartbeat_timer.cancel()
                self.heartbeat_timer = None

    def enter_func(self, request, response):
        self.get_logger().info("Lidar entering operation mode")
        self.reset_value()
        self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
        response.success = True
        response.message = 'Entered'
        return response

    def exit_func(self, request, response):
        self.get_logger().info('Lidar exiting operation mode')
        self.reset_value()
        response.success = True
        response.message = 'Exited'
        return response

    def heartbeat_srv_cb(self, request, response):
        if self.heartbeat_timer:
            self.heartbeat_timer.cancel()
            self.heartbeat_timer = None
        if request.data:
            self.heartbeat_timer = Timer(5, self.trigger_exit)
            self.heartbeat_timer.start()
        response.success = request.data
        return response

    def trigger_exit(self):
        self.get_logger().info("Heartbeat timeout. Exiting operation mode.")
        # 使用服务调用退出
        client = self.create_client(Trigger, '/lidar_app/exit')
        while not client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('/lidar_app/exit service not available, waiting...')
        request = Trigger.Request()
        future = client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        if future.result() is not None:
            self.get_logger().info('Exit service response: %s' % future.result().message)
        else:
            self.get_logger().error('Failed to call exit service')

    def lidar_callback(self, lidar_data: LaserScan):
        ranges = list(lidar_data.ranges)
        ranges = [9999.0 if r < 0.05 else r for r in ranges]  # 小于5cm当作无限远 (treat distances less than 5cm as infinity)
        twist = Twist()

        with self.lock:
            try:
                min_index = np.nanargmin(np.array(ranges))  # 找出距离最小值 (find out the minimum value of distance)
                dist = ranges[min_index]
                angle = lidar_data.angle_min + lidar_data.angle_increment * min_index  # 计算最小值对应的角度 (calculate the angle corresponding to the minimum value)
                angle = angle if angle < math.pi else angle - math.pi * 2  # 处理角度 (handle angle)
                self.get_logger().debug(f"Min distance: {dist:.2f} meters at angle: {math.degrees(angle):.2f} degrees")
            except ValueError:
                self.get_logger().warn("All ranges are NaN or empty.")
                return

            # 避障 (obstacle avoidance)
            if self.running_mode == 1 and self.timestamp <= time.time():
                if abs(angle) < self.scan_angle / 2 and dist < self.threshold:
                    twist.linear.x = self.speed / 6
                    twist.angular.z = self.speed * 3 * -np.sign(angle)
                    self.timestamp = time.time() + 0.8
                    self.get_logger().info(f"Obstacle Avoidance: Adjusting direction towards {math.degrees(angle):.2f} degrees")
                else:
                    twist.linear.x = self.speed
                    twist.angular.z = 0.0
                self.velocity_pub.publish(twist)

            # 追踪 (tracking)
            elif self.running_mode == 2 and self.timestamp <= time.time():
                self.get_logger().debug("Entering tracking logic")
                if abs(angle) < self.scan_angle / 2:
                    if dist < self.threshold and abs(math.degrees(angle)) > 10:
                        twist.linear.x = 0.01  # 微小前进，用于微调方向
                        twist.angular.z = self.speed * 3 * -np.sign(angle)
                        self.timestamp = time.time() + 0.4
                        self.get_logger().info(f"Tracking: Adjusting direction towards {math.degrees(angle):.2f} degrees")
                    elif self.threshold <= dist < 0.35:
                        twist.linear.x = self.speed  # 正常前进
                        twist.angular.z = 0.0
                        self.timestamp = time.time() + 0.4
                        self.get_logger().info("Tracking: Moving forward")
                    else:
                        twist.linear.x = 0.0
                        twist.angular.z = 0.0
                        self.get_logger().info("Tracking: Stopping")
                else:
                    twist.linear.x = 0.0
                    twist.angular.z = 0.0
                    self.get_logger().info("Tracking: Target out of scan angle")
                self.velocity_pub.publish(twist)

            # 警卫看守 (guard duty)
            elif self.running_mode == 3 and self.timestamp <= time.time():
                if dist < self.threshold and abs(math.degrees(angle)) > 10:
                    twist.linear.x = 0.01  # 微小前进，用于微调方向
                    twist.angular.z = self.speed * 3 * -np.sign(angle)
                    self.timestamp = time.time() + 0.4
                    self.get_logger().info(f"Guard Duty: Adjusting direction towards {math.degrees(angle):.2f} degrees")
                else:
                    twist.linear.x = 0.0
                    twist.angular.z = 0.0
                    self.get_logger().info("Guard Duty: Stopping")
                self.velocity_pub.publish(twist)

    def set_running_srv_callback(self, request, response):
        new_running_mode = request.data
        self.get_logger().info(f"Setting running mode to {new_running_mode}")
        if not 0 <= new_running_mode <= 3:
            response.success = False
            response.message = f"Invalid running mode {new_running_mode}"
        else:
            with self.lock:
                self.running_mode = new_running_mode
                self.velocity_pub.publish(Twist())
            response.success = True
            response.message = f"Running mode set to {new_running_mode}"
        return response

    def set_parameters_srv_callback(self, request, response):
        new_threshold, new_scan_angle, new_speed = request.data
        self.get_logger().info(f"Setting new parameters: threshold={new_threshold:.2f}, scan_angle={new_scan_angle:.2f}, speed={new_speed:.2f}")
        if not 0.3 <= new_threshold <= 1.5:
            response.success = False
            response.message = f"Threshold {new_threshold:.2f} is out of range (0.3 ~ 1.5)"
        elif new_speed <= 0:
            response.success = False
            response.message = "Speed must be greater than 0"
        else:
            with self.lock:
                self.threshold = new_threshold
                self.scan_angle = math.radians(new_scan_angle)
                self.speed = new_speed  # 移除缩放因子
            response.success = True
            response.message = "Parameters updated successfully"
        return response

def main(args=None):
    rclpy.init(args=args)
    lidar_controller = LidarController()
    try:
        rclpy.spin(lidar_controller)
    except KeyboardInterrupt:
        lidar_controller.get_logger().info('Shutting down LidarController node.')
    finally:
        lidar_controller.reset_value()
        lidar_controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
