#!/usr/bin/python3
# coding=utf8
import numpy as np
import cv2
import rclpy
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from rclpy.node import Node
import json
from rcl_interfaces.srv import GetParameters

class ColorDetect(Node):
    def __init__(self):
        super().__init__('color_detect')
        self.create_subscription(Image, '/image_raw', self.image_callback, 10)
        self.bridge = CvBridge()

        node_name = '/param_publisher'
        param_name = '/lab_config_manager/color_range_list'

        try:
            self.color_range_list = self.get_remote_param(node_name, param_name)
            self.get_logger().info(f'Loaded color ranges: {self.color_range_list}')
        except Exception as e:
            self.get_logger().error(f'Failed to load color ranges: {e}')
            self.color_range_list = {}

    def get_remote_param(self, node_name, param_name):
        client = self.create_client(GetParameters, f'{node_name}/get_parameters')
        
        while not client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info(f'Waiting for {node_name} parameter service...')
        
        request = GetParameters.Request()
        request.names = [param_name]
        future = client.call_async(request)
        rclpy.spin_until_future_complete(self, future)

        if future.result() is not None and len(future.result().values) > 0:
            param_value = future.result().values[0]
            return json.loads(param_value.string_value)
        else:
            raise RuntimeError(f"Failed to get parameter {param_name} from {node_name}")

    def run(self, img):
        img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        try:
            red_min = np.array(self.color_range_list['red']['min'], dtype=np.uint8)
            red_max = np.array(self.color_range_list['red']['max'], dtype=np.uint8)
        except KeyError as e:
            self.get_logger().error(f'Missing key in color range: {e}')
            return img

        mask = cv2.inRange(img_hsv, red_min, red_max)
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for c in contours:
            area = cv2.contourArea(c)
            if area > 100:
                ((centerX, centerY), radius) = cv2.minEnclosingCircle(c)
                centerX = int(centerX)
                centerY = int(centerY)
                radius = int(radius)
                cv2.circle(img, (centerX, centerY), radius, (0, 0, 255), 2)  
                cv2.putText(img, 'Red Detected', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

        return img

    def image_callback(self, ros_image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(ros_image, "bgr8")
            frame_result = self.run(cv_image)
            cv2.imshow('Frame', frame_result)
            cv2.waitKey(1)
        except Exception as e:
            self.get_logger().error(f"Failed to process image: {e}")

def main(args=None):
    rclpy.init(args=args)
    color_detect = ColorDetect()
    rclpy.spin(color_detect)
    color_detect.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
