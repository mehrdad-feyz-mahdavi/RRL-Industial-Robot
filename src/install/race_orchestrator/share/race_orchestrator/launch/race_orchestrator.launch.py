from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Race Manager Node
        Node(
            package='race_orchestrator',
            executable='race_manager',
            name='race_manager',
            output='screen'
        ),
        
        # Web Interface Node
        Node(
            package='race_orchestrator',
            executable='web_interface',
            name='web_interface',
            output='screen'
        )
    ]) 