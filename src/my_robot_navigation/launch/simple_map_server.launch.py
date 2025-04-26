from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get the package directory
    pkg_dir = get_package_share_directory('my_robot_navigation')
    
    # Create a simple map.yaml file
    map_yaml_content = f"""
image: {os.path.join(pkg_dir, 'maps', 'map.pgm')}
mode: trinary
resolution: 0.05
origin: [-3.32, -2.86, 0]
negate: 0
occupied_thresh: 0.65
free_thresh: 0.25
    """
    
    # Write the yaml file
    temp_yaml = '/tmp/simple_map.yaml'
    with open(temp_yaml, 'w') as f:
        f.write(map_yaml_content)

    # Create the map server node
    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{
            'yaml_filename': temp_yaml,
            'use_sim_time': False,
            'frame_id': 'map'
        }]
    )

    return LaunchDescription([
        map_server
    ]) 