from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_dir = get_package_share_directory('my_robot_camera')
    model_path = os.path.join(pkg_dir, 'models', 'best.pt')
    
    return LaunchDescription([
        # Camera node with BEST_EFFORT QoS
        Node(
            package='my_robot_camera',
            executable='camera_node',
            name='camera_node',
            parameters=[{
                'camera_id': 0,
                'frame_id': 'camera_link',
                'width': 640,
                'height': 480,
                'fps': 15,
                'exposure': -1,
                'buffer_size': 1,
                'queue_size': 30,
                'model_path': model_path,
                'confidence_threshold': 0.1,
                'enable_detection': True
            }],
            output='screen'
        ),
        
        # QoS Bridge node
        Node(
            package='my_robot_camera',
            executable='qos_bridge_node',
            name='qos_bridge_node',
            output='screen'
        )
    ]) 