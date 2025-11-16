# MEMO

## STOP PROCESSES

Execute this command before starting any new process

```bash
~/.stop_ros.sh
```

## [LIDAR](https://docs.hiwonder.com/projects/PuppyPi/en/latest/docs/30.ROS2_Lidar_Course.html)

Lidar is a remote sensing device that utilizes laser technology to detect the position and speed of targets. Lidar offers high-ranging resolution, strong penetrability, excellent anti-interference ability, and remarkable anti-stealth capability.

The PuppyPi robot is designed to track objects directly in front of it. If the target deviates more than 10 degrees from the center of its field of view, the robot will rotate in place to realign with the target. Additionally, when an obstacle is detected, PuppyPi will automatically steer away to avoid a collision.

### Init LIDAR

```bash
ros2 launch app lidar_node.launch.py
```

### Start LIDAR game

```bash
ros2 service call /lidar_app/enter std_srvs/srv/Trigger {}
```

### Start Obstacle Avoidance

```bash
ros2 service call /lidar_app/set_running puppy_control_msgs/srv/SetInt64 data:\ 1
```

### Stop Obstacle Avoidance

```bash
ros2 service call /lidar_app/set_running puppy_control_msgs/srv/SetInt64 data:\ 0
```

### Stop LIDAR game

```bash
ros2 service call /lidar_app/exit std_srvs/srv/Trigger {}
```

### Program

#### Launch

The Launch file path is **/home/ubuntu/ros2_ws/src/app/launch/lidar_node.launch.py**

```python3
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Define the paths to the launch files
    lidar_launch_path = os.path.join(get_package_share_directory('peripherals'), 'launch', 'lidar.launch.py')
    puppy_control_launch_path = os.path.join('/home/ubuntu/ros2_ws/src/driver/puppy_control/launch', 'puppy_control.launch.py')

    return LaunchDescription([
        # Include the lidar launch file
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(lidar_launch_path)
        ),

        # Node for lidar application
        Node(
            package='app',
            executable='lidar',
            name='lidar_app',
            output='screen'
        ),

        # Include the puppy control launch file
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(puppy_control_launch_path)
        ),
    ])
```

#### Source code

The source code of this program is stored in **/home/ubuntu/ros2_ws/src/app/app/lidar.py**

```python3
class LidarController(Node):
    def __init__(self, name):
        # Invokes the constructor of the parent class to initialize the node with the specified name.
        super().__init__(name)
        # Defines the operating mode—1 for “Lidar Obstacle Avoidance Mode” and 2 for “Lidar Guard Mode”.
        self.running_mode = 0   # 0: Radar obstacle-avoidance mode, 1: Radar obstacle avoidance mode, 2: Radar guard mode
        # Sets a distance threshold of 0.9 meters. In Obstacle Avoidance Mode, if an object is detected within this range, avoidance behavior may be triggered.
        self.threshold = 0.9    # meters (distance threshold)
        # Specifies the scan angle, set to 90 degrees (converted to radians), representing the forward detection range.
        self.scan_angle = math.radians(90)  # radians: the forward scanning angle
        # Defines the robot’s movement speed in Obstacle Avoidance Mode, measured in meters per second
        self.speed = 0.12       # speed in meters per second for obstacle avoidance mode
        # Components used to manage data synchronization and locking to ensure consistent and reliable data handling.
        self.timestamp = 0
        self.lock = RLock()
        self.lidar_sub = None
        self.heartbeat_timer = None

        # Create Publisher
        self.velocity_pub = self.create_publisher(Twist, '/cmd_vel_nav', 10)
        self.velocity_pub.publish(Twist())

        # Create service
        self.enter_srv = self.create_service(Trigger, '/lidar_app/enter', self.enter_func)
        self.exit_srv = self.create_service(Trigger, '/lidar_app/exit', self.exit_func)
        self.heartbeat_srv = self.create_service(SetBool, '/lidar_app/heartbeat', self.heartbeat_srv_cb)
        self.set_running_srv = self.create_service(SetInt64, "/lidar_app/set_running", self.set_running_srv_callback)
        self.set_parameters_srv = self.create_service(SetFloat64List, "/lidar_app/adjust_parameters", self.set_parameters_srv_callback)
```

#### Obstacle Avoidance

```python3
    def lidar_callback(self, lidar_data: LaserScan):
        ranges = list(lidar_data.ranges)

```undefined
    ranges = [9999.0 if r < 0.05 else r for r in ranges]  # treat distances less than 5cm as infinity
```

        twist = Twist()

        with self.lock:
            min_index = np.nanargmin(np.array(ranges))  # Trova la distanza minima (find out the minimum value of distance)
            dist = ranges[min_index]
            angle = lidar_data.angle_min + lidar_data.angle_increment * min_index  # Calcolare l'angolo corrispondente al valore minimo (calculate the angle corresponding to the minimum value)
            angle = angle if angle < math.pi else angle - math.pi * 2  # 处理角度 (handle angle)

            # Obstacle avoidance
            # Checks whether the robot is in obstacle avoidance mode (running_mode == 1) and if the timestamp condition is met
            if self.running_mode == 1 and self.timestamp <= time.time():
                # Determines if the target obstacle is within the forward scanning range and if the distance to the obstacle is less than the set threshold.
                if abs(angle) < self.scan_angle / 2 and dist < self.threshold:
                    # Sets the linear velocity to one-sixth of self.speed, slowing down the robot’s forward movement
                    twist.linear.x = self.speed / 6
                    # Sets the angular velocity to rotate the robot away from the obstacle based on it
                    twist.angular.z = self.speed * 3 * -np.sign(angle)
                    # Updates the timestamp to delay further obstacle avoidance actions for 0.8 seconds
                    self.timestamp = time.time() + 0.8
                else:
                    # If no obstacle is within range, the robot continues to move forward with a linear velocity of self.speed and an angular velocity of 0.
                    twist.linear.x = self.speed
                    twist.angular.z = 0.0
                # Publishes the Twist message to update the robot’s velocity accordingly
                self.velocity_pub.publish(twist)
```

## SLAM

The project is located in the Docker container at */home/ubuntu/ros2_ws/src/slam*

### Start SLAM Mapping

```bash
ros2 launch slam slam.launch.py
```

The command launches:

- base_launch: Launches the required hardware for the system => camera, lidar, chassis
- slam_launch: Launches the basic mapping setup => use_sim_time, map_frame, odom_frame, base_frame
- puppy_control: Launches the motion control setup

- bringup_launch: initial pose

The launch file is located in the Docker container at: /home/ubuntu/ros2_ws/src/slam/launch/slam.launch.py

### Launch RViz tool to display the mapping results

```bash
ros2 launch slam rviz_slam.launch.py
```

### Cattura mappa

```bash
cd ~/ros2_ws/src/slam/maps && ros2 run nav2_map_server map_saver_cli -f "map_01" --ros-args -p map_subscribe_transient_local:=true
```