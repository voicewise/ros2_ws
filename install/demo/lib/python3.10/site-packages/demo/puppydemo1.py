#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Float32
from cv_bridge import CvBridge
import cv2
import mediapipe as mp

class PuppyCameraControl(Node):
    def __init__(self):
        super().__init__('puppy_camera_control_node')

        self.declare_parameter('Stand.stance_x', 0.0)
        self.stance_x = self.get_parameter('Stand.stance_x').value

        self.bridge = CvBridge()
        
        self.publisher_ = self.create_publisher(Float32, 'stance_x', 10)

        self.cap = cv2.VideoCapture(0)

        self.timer = self.create_timer(0.1, self.timer_callback)

        self.mp_face_detection = mp.solutions.face_detection
        self.face_detection = self.mp_face_detection.FaceDetection(model_selection=0, min_detection_confidence=0.5)
        self.mp_drawing = mp.solutions.drawing_utils

    def timer_callback(self):
        ret, frame = self.cap.read()
        if not ret:
            return

        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        results = self.face_detection.process(rgb_frame)

        if results.detections:
            self.stance_x += 0.1
            self.set_parameters([rclpy.parameter.Parameter('Stand.stance_x', rclpy.Parameter.Type.DOUBLE, self.stance_x)])
            self.publish_stance_x()

            for detection in results.detections:
                self.mp_drawing.draw_detection(frame, detection)

        cv2.imshow("Camera", frame)
        cv2.waitKey(1)

    def publish_stance_x(self):
        msg = Float32()
        msg.data = self.stance_x
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published modified stance_x: {self.stance_x}')

def main(args=None):
    rclpy.init(args=args)
    node = PuppyCameraControl()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.destroy_node()
    rclpy.shutdown()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()

