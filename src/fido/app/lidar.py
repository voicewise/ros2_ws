#!/usr/bin/env python3
# Description: utilizzo del lidar per evitare ostacoli
# Project: FIDO
# Author: hiwonder + Luigi T.
# coding=utf8
# Date: 2021/09/27
# Update: 2025/11/11

import math
import time
import rclpy
from rclpy.node import Node
from threading import Timer, RLock
import numpy as np
# Twist è un tipo di messaggio ROS 2 che rappresenta la velocità e la rotazione di un robot
# e viene utilizzato per comunicare comandi di movimento a un robot mobile.
# Twist  contiene due componenti principali:
# - linear: rappresenta la velocità lineare del robot lungo gli assi x, y, z (in metri al secondo)
# - angular: rappresenta la velocità angolare (rotazione) attorno agli assi x, y, z (in radianti al secondo)
from geometry_msgs.msg import Twist         # This expresses velocity in free space broken into its linear and angular parts (vector3).

from sensor_msgs.msg import LaserScan
from std_srvs.srv import SetBool, Trigger
from puppy_control_msgs.srv import *

MAX_SCAN_ANGLE = 360  # Angolo di scansione laser (the scanning angle of the laser)

class LidarController(Node):

    def __init__(self, name):
        super().__init__(name)
        self.running_mode = 0               # 1: Modalità di evitamento degli ostacoli 2: Modalità guardia radar, 3: modalità di guardia (1: Radar obstacle avoidance mode, 2: Radar guard mode, 3. guard duty mode)
        self.threshold = 0.9                # meters - soglia di distanza in metri (distance threshold)
        self.scan_angle = math.radians(90)  # radians - angolo di scansione in avanti (the forward scanning angle)
        self.speed = 0.12                   # Velocità in metri al secondo i modalità evitamento ostacoli (speed in meters per second for obstacle avoidance mode)
        self.timestamp = 0                  # Timestamp
        # Rlock è un meccanismo di sincronizzazione che protegge l'accesso a risorse condivise in ambienti multi-thread.
        # Consente a uno stesso thread di acquisire il lock più volte senza causare deadlock mantenendo un contatore interno
        # che registra quante volte è stato acquisito dal medesimo thread
        # garantisce che i dati sensibili (come running_mode, threshold, timestamp) non vengano modificati contemporaneamente da
        # thread diversi, mantendo la coerenza dello stato del robot
        self.lock = RLock()                 # protegge la sezione di codice che elabora i dati del lidar da possibili race condition (conflitti di accesso simultaneo).
        self.lidar_sub = None
        self.heartbeat_timer = None

        self.move_srv_cb = None
        self.talk_srv_cb = None

        # Crea publisher
        self.velocity_pub = self.create_publisher(Twist, '/cmd_vel_nav', 10)
        self.velocity_pub.publish(Twist())

        # Crea servizio
        self.enter_srv = self.create_service(Trigger, '/lidar_app/enter', self.enter_func)
        self.exit_srv = self.create_service(Trigger, '/lidar_app/exit', self.exit_func)
        self.heartbeat_srv = self.create_service(SetBool, '/lidar_app/heartbeat', self.heartbeat_srv_callback)
        self.set_running_srv = self.create_service(SetInt64, "/lidar_app/set_running", self.set_running_srv_callback)
        self.set_parameters_srv = self.create_service(SetFloat64List, "/lidar_app/adjust_parameters", self.set_parameters_srv_callback)

        # Funzioni estese
        self.move_srv = self.create_service(SetBool, '/lidar_app/move', self.move_srv_callback)
        self.talk_srv = self.create_service(SetBool, '/lidar_app/talk', self.talk_srv_callback)

        self.logger =  self.get_logger()

    # Reset the values of the LidarController object.
    def reset_state(self):
        self.running_mode = 0
        self.threshold = 0.3
        self.speed = 0.12
        self.scan_angle = math.radians(90)

        #  If the lidar_sub exists, it unsubscribes from the topic and sets the lidar_sub to None.
        if self.lidar_sub is not None:
            self.lidar_sub.destroy()
            self.lidar_sub = None

    # callback function for a service that allows the Lidar controller to enter operation mode.
    def enter_func(self, request, response):
        self.get_logger().info("Lidar entering operation mode")
        self.reset_state()
        self.lidar_sub = self.create_subscription(LaserScan, '/scan', self.lidar_callback, 10)
        response.success = True
        response.message = 'Entered'
        return response

    # handles the exit operation mode
    def exit_func(self, request, response):
        self.get_logger().info('Lidar exiting operation mode')
        self.reset_state()
        if self.heartbeat_timer:
            self.heartbeat_timer.cancel()
        response.success = True
        response.message = 'Exited'
        return response

    # callback function for the service heartbeat_srv
    def heartbeat_srv_callback(self, request, response):
        if self.heartbeat_timer:
            self.heartbeat_timer.cancel()
        if request.data:
            self.heartbeat_timer = Timer(5, self.exit_func, [Trigger.Request(), Trigger.Response()])
            self.heartbeat_timer.start()
        response.success = request.data
        return response

    # processes the lidar data to control the robot's movement in different modes (obstacle avoidance, tracking, and guard duty).
    def lidar_callback(self, lidar_data: LaserScan):
        # treat distances less than 5cm as infinity
        ranges = list(lidar_data.ranges)
        # Replace any range values less than 0.05 (5cm) with 9999.0 to represent infinite distance.
        ranges = [9999.0 if r < 0.05 else r for r in ranges]  # Meno di 5 cm è considerato infinito ()

        twist = Twist()     # create a Twist message object to control the robot's movement

        # If the lidar_sub is None, it means the Lidar controller is not in operation mode, so it returns.
        with self.lock: # acquisisce il lock non eppane si entra nel blocco e lo rilascia non appena esce per evitare race condition conflitti

            # find out the minimum value of distance
            min_index = np.nanargmin(np.array(ranges))  # Trova la distanza minima ()
            dist = ranges[min_index]                    # imposta la distanza minima

            # calculate the angle corresponding to the minimum value
            angle = lidar_data.angle_min + lidar_data.angle_increment * min_index  # Calcolare l'angolo corrispondente al valore minimo

            # Normalize the angle to be within -pi to pi
            angle = angle if angle < math.pi else angle - math.pi * 2  # angolo di lavorazione (handle angle)

            # Mode 1: Radar obstacle avoidance mode - aggiramento osctacolo, continua finchè l'ostacolo non è superato
            if self.running_mode == 1 and self.timestamp <= time.time():
                # If the angle is within the scan angle and the distance is less than the threshold
                if abs(angle) < self.scan_angle / 2 and dist < self.threshold:
                    # riduce la velocità del robot lungo asse x rispetto al valore base (self.speed) memorizzato
                    twist.linear.x = self.speed / 6
                    # imposta la velocità angolare di rotazione del robot attorno all'asse z (verticale) nella direzione di rotazione definita
                    # la funzone np.sign(angle) restituisce 1 se angle > 0 (ostacolo a dx) e -1 se angle < 0 (ostacolo a sx)
                    # Il segno negativo (-np.sign()) inverte il risultato, quindi il robot ruota verso il lato opposto dell'ostacolo,
                    # implementando un comportamento di evitamento naturale e reattivo.
                    twist.angular.z = self.speed * 3 * -np.sign(angle)
                    # Imposta un meccanismo di debouncing o delay che evita l'esecuzione troppo frequente di determinate azioni nel robot.
                    # L'azione successiva verra' eseguita solo quando il tempo attuale supera self.timestamp.
                    self.timestamp = time.time() + 0.8
                else:
                    # ripsristina la velocità lineare in avanti del robot
                    twist.linear.x = self.speed
                    # ferma la rotazione del robot attorno all'asse z
                    twist.angular.z = 0.0
                self.velocity_pub.publish(twist)

            # Mode 2: Radar obstacle avoidance mode
            elif self.running_mode == 2 and self.timestamp <= time.time():
                # verifica se un ostacolo rilevato dal lidar si trova entro l'angolo di scansione frontale del robot (zona di interesse)
                if abs(angle) < self.scan_angle / 2:
                    # verifica se l'ostacolo sia più vicino del limite di sicurezza e che l'angolo assoluto sia maggiore di 10 gradi
                    if dist < self.threshold and abs(math.degrees(angle)) > 10:  # Controlla sinistra e destra (control the left and the right)
                        twist.linear.x = 0.01  # Correzione nella direzione X (correction in the x-direction)
                        twist.angular.z = self.speed * 3 * np.sign(angle) # imposta velocità angolare
                        self.timestamp = time.time() + 0.4 # imposta il meccanismo di debouncing o delay
                    else:
                        # se l'ostacolo è viciono del limite massimo ma più lontano del limite minimo (0.35mt)
                        if dist < self.threshold and dist > 0.35:
                            # ripsristina la velocità lineare in avanti del robot
                            twist.linear.x = self.speed
                            # ferma la rotazione del robot attorno all'asse z
                            twist.angular.z = 0.0
                            # imposta il meccanismo di debouncing o delay
                            self.timestamp = time.time() + 0.4
                        else:
                            # ferma il movimento in avanti del robot e la rotazione
                            twist.linear.x = 0.0
                            twist.angular.z = 0.0
                else:
                    # ferma il movimento in avanti del robot e la rotazione
                    twist.linear.x = 0.0
                    twist.angular.z = 0.0
                self.velocity_pub.publish(twist)

            # Mode 3: guard duty
            elif self.running_mode == 3 and self.timestamp <= time.time():
                # verifica se l'ostacolo sia più vicino del limite di sicurezza e che l'angolo sia maggiore di 10 gradi
                if dist < self.threshold and abs(math.degrees(angle)) > 10:
                    twist.linear.x = 0.01  # Rallenta spostamento in avanti - correction in the x-direction
                    twist.angular.z = self.speed * 3 * np.sign(angle) # imposta velocità angolare
                    self.timestamp = time.time() + 0.4 # imposta il meccanismo di debouncing o delay
                else:
                    # ferma il movimento in avanti del robot e la rotazione
                    twist.linear.x = 0.0
                    twist.angular.z = 0.0
                self.velocity_pub.publish(twist)

    # callback to set the running mode of the robot
    def set_running_srv_callback(self, request, response):
        new_running_mode = request.data # get the new running mode
        self.get_logger().info(f"Setting running mode to {new_running_mode}")
        if not 0 <= new_running_mode <= 3:
            response.success = False
            response.message = f"Invalid running mode {new_running_mode}"
        else:
            self.running_mode = new_running_mode
            self.velocity_pub.publish(Twist())
            response.success = True
            response.message = f"Running mode set to {new_running_mode}"
        return response

    def talk_srv_callback(self, request, response):
        talk_request = request.data # get the talk request
        self.get_logger().info(f"Executing talk request {talk_request}")
        response.success = True
        response.message = f"Talk request received: {talk_request}"
        return response

    def move_srv_callback(self, request, response):
        talk_request = request.data # get the talk request
        self.get_logger().info(f"Executing move request {talk_request}")
        response.success = True
        response.message = f"Move request received: {talk_request}"
        return response

    # updates parameters (threshold, scan angle, and speed) for the Lidar controller
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
            self.threshold = new_threshold
            self.scan_angle = math.radians(new_scan_angle)
            self.speed = new_speed * 0.002
            response.success = True
            response.message = "Parameters updated successfully"
        return response

# sets up and runs a ROS2 node, handling cleanup when the node is stopped.
def main(args=None):
    rclpy.init(args=args)               # Initialize the ROS 2 environment
    node = LidarController('lidar_app') # create an instance of the LidarController node
    try:
        rclpy.spin(node)                # Keep the node running until it is shut down
    except KeyboardInterrupt:           # Handle keyboard interrupt gracefully
        pass
    finally:
        node.destroy_node()             # Destroy the node
        rclpy.shutdown()                # Shutdown the ROS 2 environment

if __name__ == '__main__':              # Ensure the script runs only when executed directly
    main()
