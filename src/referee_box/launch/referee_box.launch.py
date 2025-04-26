import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Get the package directory
    referee_box_dir = get_package_share_directory('referee_box')
    
    # Path to the configuration file
    config_file = os.path.join(referee_box_dir, 'referee_box', 'config', 'referee_config.yaml')
    
    # Create the referee box node
    referee_box_node = Node(
        package='referee_box',
        executable='referee_box_node',
        name='referee_box',
        output='screen',
        parameters=[config_file],
        remappings=[
            ('/referee/state', '/referee/state'),
            ('/referee/score', '/referee/score'),
            ('/referee/emergency', '/referee/emergency'),
            ('/robot/pose', '/robot/pose'),
            ('/robot/status', '/robot/status')
        ]
    )
    
    return LaunchDescription([
        referee_box_node
    ]) 