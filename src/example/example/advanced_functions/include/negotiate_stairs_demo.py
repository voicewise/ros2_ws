#!/usr/bin/python3
# coding=utf8
import sys
import cv2
import time
import math
import numpy as np
from enum import Enum
import yaml
from sdk import Misc
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile
from sensor_msgs.msg import Image
from std_srvs.srv import Empty, SetBool
from interfaces.srv import *
from puppy_control_msgs.msg import Velocity, Pose, Gait
from puppy_control_msgs.srv import SetRunActionName
from cv_bridge import CvBridge

ROS_NODE_NAME = 'negotiate_stairs_demo'

class PuppyStatus(Enum):
    LOOKING_FOR = 0  # ricerca in corso
    FOUND_TARGET = 3  # L'obiettivo della scala è stato trovato
    DOWN_STAIRS = 4  # Scendi le scale
    STOP = 10
    END = 20            

def getAreaMaxContour(contours):
    contour_area_temp = 0
    contour_area_max = 0
    area_max_contour = None

    for c in contours:
        contour_area_temp = math.fabs(cv2.contourArea(c))
        if contour_area_temp > contour_area_max:
            contour_area_max = contour_area_temp
            if contour_area_temp >= 5:
                area_max_contour = c
    return area_max_contour, contour_area_max

class NegotiateStairsDemo(Node):
    def __init__(self):
        super().__init__(ROS_NODE_NAME)
        self.bridge = CvBridge()

        # Inizializza le variabili di istanza
        self.is_shutdown = False
        self.is_running = True
        self.target_centre_point = None
        self.PuppyPose = None
        self.action_group_executed = False
        self.up_stairs_time = 0  # Registra quando inizia l'azione di salire le scale

        # Carica i parametri della soglia del colore
        self.color_range_list = self.get_color_ranges()

        # colore di destinazione
        self.target_color = ['red']
        self.puppyStatus = PuppyStatus.LOOKING_FOR
        self.puppyStatusLast = PuppyStatus.END

        # Inizializzare editori e sottoscrittori
        qos_profile = QoSProfile(depth=10)
        self.velocity_publisher = self.create_publisher(Velocity, '/puppy_control/velocity', qos_profile)
        self.pose_publisher = self.create_publisher(Pose, '/puppy_control/pose', qos_profile)
        self.gait_publisher = self.create_publisher(Gait, '/puppy_control/gait', qos_profile)
        self.image_subscriber = self.create_subscription(Image, '/image_raw', self.image_callback, qos_profile)

        # Inizializza l'agente di servizio
        self.run_action_group_srv = self.create_client(SetRunActionName, '/puppy_control/runActionGroup')
        while not self.run_action_group_srv.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('等待 /puppy_control/runActionGroup 服务...')

        # Temporizzatore di inizializzazione, 100 Hz
        self.timer = self.create_timer(0.01, self.move)
        #self.get_logger().info(il nodo f'{ROS_NODE_NAME} è stato avviato.')

    def get_color_ranges(self):
        try:
            with open('/home/ubuntu/software/lab_tool/lab_config.yaml', 'r') as file:
                config = yaml.safe_load(file)
                color_ranges = config.get('color_range_list', {})
                return color_ranges
        except Exception as e:
            self.get_logger().error(f'Impossibile caricare la configurazione del colore: {e}')
            sys.exit(1)

    def move(self):
        # Aggiungi la logica della macchina a stati
        if self.puppyStatus == PuppyStatus.LOOKING_FOR:
            if self.target_centre_point and self.target_centre_point[1] > 400:  # Determina la posizione di destinazione
                self.puppyStatus = PuppyStatus.FOUND_TARGET
                velocity_msg = Velocity()
                velocity_msg.x = 0.0
                velocity_msg.y = 0.0
                velocity_msg.yaw_rate = 0.0
                self.velocity_publisher.publish(velocity_msg)
                self.up_stairs_time = time.time()
                self.action_group_executed = False  # Reimposta il flag di esecuzione del gruppo di azioni
                #self.get_logger().info('Scopri il target e preparati ad eseguire il gruppo di azioni.')
            else:
                # Se non sei vicino alle scale, continua ad andare avanti
                velocity_msg = Velocity()
                velocity_msg.x = 10.0  # vai avanti
                velocity_msg.y = 0.0
                velocity_msg.yaw_rate = 0.0
                self.velocity_publisher.publish(velocity_msg)

        elif self.puppyStatus == PuppyStatus.FOUND_TARGET:
            # Assicurati che il gruppo di azioni continui ad essere eseguito quando è vicino al punto target
            if not self.action_group_executed:
                self.run_action_group('up_stairs_2cm.d6ac', True)  # Chiama gruppo di azioni
                self.action_group_executed = True

            # controllo del timeout
            if time.time() - self.up_stairs_time > 25:
                self.puppyStatus = PuppyStatus.DOWN_STAIRS
                pose_msg = Pose()
                pose_msg.stance_x = 0.0
                pose_msg.stance_y = 0.0
                pose_msg.x_shift = 0.0
                pose_msg.height = 0.3
                pose_msg.roll = 0.0
                pose_msg.pitch = 0.0
                pose_msg.yaw = 0.0
                pose_msg.run_time = 500
                self.pose_publisher.publish(pose_msg)
                self.get_logger().info('Timeout, ingresso stato DOWN_STAIRS.')

        elif self.puppyStatus == PuppyStatus.DOWN_STAIRS:
            velocity_msg = Velocity()
            velocity_msg.x = 14.0  # Velocità di discesa
            velocity_msg.y = 0.0
            velocity_msg.yaw_rate = 0.0
            self.velocity_publisher.publish(velocity_msg)
            self.get_logger().info('Sto scendendo le scale.')
            self.puppyStatus = PuppyStatus.END

        # registro dello stato
        if self.puppyStatusLast != self.puppyStatus:
            self.get_logger().info(f'puppyStatus: {self.puppyStatus}')
        self.puppyStatusLast = self.puppyStatus

    def run_action_group(self, action_name, wait):
        request = SetRunActionName.Request()
        request.name = action_name
        request.wait = wait
        self.get_logger().info(f'调用 runActionGroup 服务，动作组名称: {action_name}')
        future = self.run_action_group_srv.call_async(request)
        future.add_done_callback(self.run_action_group_callback)

    def run_action_group_callback(self, future):
        try:
            response = future.result()
            self.get_logger().info(f'运行动作组: {response.message}')
            self.action_group_executed = False
        except Exception as e:
            self.get_logger().error(f'调用 runActionGroup 服务失败: {e}')

    def run(self, img):
        img_h, img_w = img.shape[:2]
        frame_resize = cv2.resize(img, (320, 240), interpolation=cv2.INTER_NEAREST)
        frame_gb = cv2.GaussianBlur(frame_resize, (3, 3), 3)
        frame_lab = cv2.cvtColor(frame_gb, cv2.COLOR_BGR2LAB)

        for color in self.target_color:
            if color in self.color_range_list:
                detect_color = color
                frame_mask = cv2.inRange(
                    frame_lab,
                    (self.color_range_list[detect_color]['min'][0],
                     self.color_range_list[detect_color]['min'][1],
                     self.color_range_list[detect_color]['min'][2]),
                    (self.color_range_list[detect_color]['max'][0],
                     self.color_range_list[detect_color]['max'][1],
                     self.color_range_list[detect_color]['max'][2])
                )
                opened = cv2.morphologyEx(frame_mask, cv2.MORPH_OPEN, np.ones((6, 6), np.uint8))
                closed = cv2.morphologyEx(opened, cv2.MORPH_CLOSE, np.ones((6, 6), np.uint8))

        cnts = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_TC89_L1)[-2]
        cnt_large, area_max = getAreaMaxContour(cnts)

        if cnt_large is not None:
            rect = cv2.minAreaRect(cnt_large)
            box = np.int0(cv2.boxPoints(rect))  # 最小外接矩形的四个顶点
            
            centerX = rect[0][0]
            centerY = rect[0][1]
            centerX = int(Misc.map(centerX, 0, 320, 0, img_w))
            centerY = int(Misc.map(centerY, 0, 240, 0, img_h))
            for i in range(4):
                box[i, 1] = int(Misc.map(box[i, 1], 0, 240, 0, img_h))
            for i in range(4):                
                box[i, 0] = int(Misc.map(box[i, 0], 0, 320, 0, img_w))
                
            cv2.drawContours(img, [box], -1, (0, 0, 255, 255), 2)  # 画出矩形
            self.target_centre_point = [centerX, centerY]
            cv2.circle(img, (centerX, centerY), 5, (0, 0, 255), -1)  # 画出中心点

        return img

    def image_callback(self, ros_image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(ros_image, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'图像转换失败: {e}')
            return

        frame = cv_image.copy()
        if self.is_running:
            frame_result = self.run(frame)
            if self.puppyStatus != PuppyStatus.FOUND_TARGET:
                cv2.imshow('Frame', frame_result)
                cv2.waitKey(1)

    def cleanup(self):
        self.is_shutdown = True
        velocity_msg = Velocity()
        velocity_msg.x = 0.0
        velocity_msg.y = 0.0
        velocity_msg.yaw_rate = 0.0
        self.velocity_publisher.publish(velocity_msg)
        self.get_logger().info('节点关闭，停止移动。')

    def destroy_node(self):
        self.cleanup()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = NegotiateStairsDemo()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('接收到键盘中断信号，正在关闭节点...')
    finally:
        node.destroy_node()
        rclpy.shutdown()
        cv2.destroyAllWindows()

if __name__ == '__main__':
    main()

