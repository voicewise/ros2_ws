#!/usr/bin/python3
# coding=utf8
import rclpy
from rclpy.node import Node
import yaml
import json

class ParamPublisher(Node):
    def __init__(self):
        super().__init__('param_publisher')

        self.declare_parameter('/lab_config_manager/color_range_list', "{}")
        self.load_yaml_and_publish()

    def load_yaml_and_publish(self):
        yaml_path = '/home/ubuntu/ros2_ws/src/example/example/config/lab_config_list.yaml'
        with open(yaml_path, 'r') as file:
            color_ranges = yaml.safe_load(file)['color_range_list']  
            color_ranges_str = json.dumps(color_ranges)

            self.set_parameters([
                rclpy.parameter.Parameter('/lab_config_manager/color_range_list', rclpy.Parameter.Type.STRING, color_ranges_str)
            ])

            for color_name, ranges in color_ranges.items():
                min_range = ranges['min']
                max_range = ranges['max']
                self.get_logger().info(f"Published color range for {color_name}: Min: {min_range}, Max: {max_range}")

def main(args=None):
    rclpy.init(args=args)
    param_publisher = ParamPublisher()
    rclpy.spin(param_publisher)
    param_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
