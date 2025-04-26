import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # Get the path to the package
    pkg_dir = get_package_share_directory('my_robot_navigation')
    
    # Path to the parameter files
    nav2_params_file = os.path.join(pkg_dir, 'config', 'nav2_params.yaml')
    map_file = os.path.join(pkg_dir, 'maps', 'map.yaml')

    # Include the Nav2 launch file
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory('nav2_bringup'),
            'launch', 'navigation_launch.py')
        ]),
        launch_arguments={
            'params_file': nav2_params_file,
            'map': map_file,
            'use_sim_time': 'false'
        }.items()
    )

    return LaunchDescription([
        nav2_launch
    ])