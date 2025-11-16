# PuppyPI

- Alimentato da Raspberry Pi 4B 4GB e basato su ROS
- Capace di pianificazione dell'andatura e di adozione della cinematica di collegamento
- Possiede la visione artificiale e lavora con OpenCV
- Supporta la simulazione gazebo
- Alimentazione 7.4V 2200mAh Lipo battery

- MAC ADDRESS 2c:cf:67:6e:6a:a

## Connessione

### Modalità diretta

- Accendere il PuppyPI
- Ricercare l'Access Point (router) del PuppyPI il cui nome comincia con HW- a cui seguono dei codici numerici
- Connettersi all'AP con password "hiwonder"
- Collegarsi con VNC all'IP 192.168.149.1, utente "*pi*" e password "*raspberrypi*"
- Collegamento via SSH:
```bash
    ssh pi@192.168.149.1
    password: raspberrypicd
```

### Modalità LAN

- fare la scansione della rete con il comando "arp -a -n | grep :"
- accendere il robot
- connettersi al robot con la modalità precedente
- attivare mediante la app la modalità LAN selezionando il router desiderato ed impostando la password relativa
- fare nuovamente la scansione della rete con arp o altro sw e trovare l'IP del PuppyPI (2c:cf:67:6e:6a:a)
- connettere VNC all'IP trovato utilizzando come utente "pi" e come password "raspberrypi"

sudo systemctl start wifi.service  
WIFI_STA_SSID = 'TP-Link_Mediavoice_5G'
WIFI_STA_PASSWORD = 'mediavoice22'


## [LIDAR ODOM EMU](https://docs.hiwonder.com/projects/PuppyPi/en/latest/docs/30.ROS2_Lidar_Course.html)

When using the lidar tracking function, the object to be detected should be higher than the scanning height of the lidar. This allows PuppyPi onboard lidar to effectively scan its position information. Then, the PuppyPi moves straight ahead. When an obstacle is detected, the PuppyPi will automatically turn to avoid the obstacle.

## RVIZ

Execuzione Con SLAM:

```bash
launch slam rviz_slam.launch.py
```

Esecuzione da solo:

```bash
rviz2
```

## URDF files

```bash
colcon_cd puppypi_description
cd urdf
pwd => /home/ubuntu/ros2_ws/src/simulations/puppypi_description/urdf
```

## Links

- [PuppyPI](https://www.hiwonder.com/collections/quadruped-robot/products/puppypi?variant=40213129003095)
