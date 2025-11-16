import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.actions import PushRosNamespace
from launch import LaunchDescription, LaunchService
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, GroupAction, OpaqueFunction, TimerAction

def launch_setup(context):
    compiled = os.environ['need_compile']

    # Determina i percorsi dei pacchetti in base alla variabile d'ambiente
    if compiled == 'True':
        slam_package_path = get_package_share_directory('slam')
        navigation_package_path = get_package_share_directory('navigation')
    else:
        slam_package_path = '/home/ubuntu/ros2_ws/src/slam'
        navigation_package_path = '/home/ubuntu/ros2_ws/src/navigation'

    sim = LaunchConfiguration('sim', default='false').perform(context)
    map_name = LaunchConfiguration('map', default='map_01').perform(context)
    robot_name = LaunchConfiguration('robot_name', default=os.environ['HOST']).perform(context)
    master_name = LaunchConfiguration('master_name', default=os.environ['MASTER']).perform(context)
    use_teb = LaunchConfiguration('use_teb', default='true').perform(context)

    sim_arg = DeclareLaunchArgument('sim', default_value=sim)
    map_name_arg = DeclareLaunchArgument('map', default_value=map_name)
    master_name_arg = DeclareLaunchArgument('master_name', default_value=master_name)
    robot_name_arg = DeclareLaunchArgument('robot_name', default_value=robot_name)
    use_teb_arg = DeclareLaunchArgument('use_teb', default_value=use_teb)

    use_sim_time = 'true' if sim == 'true' else 'false'
    use_namespace = 'true' if robot_name != '/' else 'false'

    # inizializzazione di vari componenti hardware.
    base_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(slam_package_path, 'launch/include/robot.launch.py')),
        launch_arguments={
            'sim': sim,
            'master_name': master_name,
            'robot_name': robot_name
        }.items(),
    )

    # algoritmo per avviare la navigazione
    navigation_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(navigation_package_path, 'launch/include/bringup.launch.py')),
        launch_arguments={
            'use_sim_time': use_sim_time,
            'map': os.path.join(slam_package_path, 'maps', map_name + '.yaml'),
            'params_file': os.path.join(navigation_package_path, 'config', 'nav2_params.yaml'),
            'namespace': robot_name,
            'use_namespace': use_namespace,
            'autostart': 'true',
            'use_teb': use_teb,
        }.items(),
    )

    # gruppo di azioni per il lancio completo del robot
    bringup_launch = GroupAction(
        actions=[
            PushRosNamespace(robot_name),   # Definisce lo spazio dei nomi del robot
            base_launch,                    # Inizializza i componenti hardware
            TimerAction(
                period=10.0,                # Ritardo nella esecuzione dell'azione
                actions=[navigation_launch],# Avvia l'algoritmo di navigazione
            ),
        ]
    )

    # Nodo per pubblicare i punti di destinazione
    publish_point_node = Node(
        package = 'navigation',         # Pacchetto contenente il nodo
        executable = 'publish_point',   # Nome dello script che pubblica i punti
        output='screen',                # Output del nodo
    )

    # Ritorna tutti gli argomenti di lancio
    return [sim_arg, map_name_arg, master_name_arg, robot_name_arg, use_teb_arg, bringup_launch,publish_point_node]

def generate_launch_description():
    return LaunchDescription([
        OpaqueFunction(function = launch_setup)
    ])

if __name__ == '__main__':
    # Crea un oggetto di descrizione del lancio
    ld = generate_launch_description()
    # Avvia il lancio
    ls = LaunchService()
    # Includi la descrizione del lancio
    ls.include_launch_description(ld)
    # Esegui il servizio di lancio
    ls.run()
