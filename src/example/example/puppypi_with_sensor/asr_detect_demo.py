#!/usr/bin/python3
#coding=utf8
# 第5课 语音识别传感器实验(Lesson 5 Voice Recognition Sensor)
import os
import sys
import rclpy
import sdk.asr as asr
import signal
from rclpy.node import Node
from ros_robot_controller_msgs.msg import RGBState, RGBsState


print('''
**********************************************************
*******************功能:语音识别例程(function: voice recognition routine)************************
**********************************************************
----------------------------------------------------------
Official website:https://www.hiwonder.com
Online mall:https://hiwonder.tmall.com
----------------------------------------------------------
Tips:
 * 按下Ctrl+C可关闭此次程序运行，若失败请多次尝试！(press Ctrl+C to close the program, please try multiple times if fail)
----------------------------------------------------------
''')


class ASRDetectDemo(Node):
    def __init__(self):
        super().__init__('asr_detect_demo')
        signal.signal(signal.SIGINT, self.stop)
        
        # 语音识别模块初始化(voice recognition module initialization)
        self.asr = asr.ASR()
        self.asr.getResult()
        self.asr.eraseWords()
        #1：循环识别模式。状态灯常亮（默认模式）(1: Loop recognition mode. The status light remains constantly on (default mode))
        #2：口令模式，以第一个词条为口令。状态灯常灭，当识别到口令词时常亮，等待识别到新的语音,并且读取识别结果后即灭掉(2: Password mode, using the first word as the password. The status light remains off; when the password is recognized, it stays on until a new voice is recognized, then turns off after reading the recognition result)
        #3：按键模式，按下开始识别，不按不识别。支持掉电保存。状态灯随按键按下而亮起，不按不亮(3: Button mode, recognition starts when the button is pressed, and stops when released. Supports power-off memory. The status light lights up when the button is pressed and goes off when released)
        self.asr.setMode(2)
        #添加的词条(added entry)
        self.asr.addWords(1, 'kai shi')
        self.asr.addWords(2, 'hong se')
        self.asr.addWords(3, 'lv se')
        self.asr.addWords(4, 'lan se')
                
                          
        self.rgb_pub = self.create_publisher(RGBsState, '/ros_robot_controller/set_rgb', 10)
        self.timer = self.create_timer(0.1, self.asr_callback)


    def asr_callback(self):
        self.data = self.asr.getResult()
        if self.data:
            self.get_logger().info(r'result:{}'.format(self.data))
            if self.data == 2:               
                self.set_rgb_show(255, 0, 0)
            elif self.data == 3:
                self.set_rgb_show(0, 255, 0)
            elif self.data == 4:
                self.set_rgb_show(0, 0, 255)
        elif self.data is None:
            self.get_logger().info('Sensor not connected!') 
            
    # 关闭检测函数(turn off detection function)       
    def stop(self):
        self.turn_off_rgb()
        self.get_logger().info('Shutting down...')
    # 关闭RGB彩灯(turn off color light)    
    def turn_off_rgb(self):
        led1 = RGBState()
        led1.id = 1
        led1.r = 0
        led1.g = 0
        led1.b = 0
        
        led2 = RGBState()
        led2.id = 2
        led2.r = 0
        led2.g = 0
        led2.b = 0
        
        msg = RGBsState()
        msg.data = [led1,led2]
        self.rgb_pub.publish(msg)
    # 设置RGB彩灯显示(set the RGB color light to display)    
    def set_rgb_show(self,r, g, b):
        led1 = RGBState()
        led1.id = 1
        led1.r = r
        led1.g = g
        led1.b = b       
        led2 = RGBState()
        led2.id = 2
        led2.r = r
        led2.g = g
        led2.b = b
        msg = RGBsState()
        msg.data = [led1,led2]
        self.rgb_pub.publish(msg)       
               


def main(args=None):
    rclpy.init(args=args)
    node = ASRDetectDemo()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.stop()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

        
           
