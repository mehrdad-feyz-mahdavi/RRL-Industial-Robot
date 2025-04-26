from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get the package directory
    pkg_dir = get_package_share_directory('my_robot_navigation')
    
    # Read and modify the map.yaml content
    with open(os.path.join(pkg_dir, 'maps', 'map.yaml'), 'r') as f:
        map_yaml = f.read()
    map_yaml = map_yaml.replace('${PACKAGE_PATH}', pkg_dir)
    
    # Create a temporary map file with the correct path
    temp_map_file = '/tmp/temp_map.yaml'
    with open(temp_map_file, 'w') as f:
        f.write(map_yaml)

    # Create the map server node
    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{
            'yaml_filename': temp_map_file,
            'use_sim_time': False,
            'frame_id': 'map'
        }]
    )

    return LaunchDescription([
        map_server
    ]) 