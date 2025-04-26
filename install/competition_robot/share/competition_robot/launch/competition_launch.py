import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # Get the package directory
    pkg_dir = get_package_share_directory('competition_robot')
    
    # Path to the parameter file
    params_file = os.path.join(pkg_dir, 'config', 'competition_params.yaml')
    
    # Declare launch arguments
    scenario_arg = DeclareLaunchArgument(
        'scenario',
        default_value='BMT',
        description='Scenario to run (BMT, BTT1, BTT2, ATT1, ATT2, Final)'
    )
    
    # Create the competition node
    competition_node = Node(
        package='competition_robot',
        executable='competition_node',
        name='competition_node',
        output='screen',
        parameters=[params_file, {'scenario': LaunchConfiguration('scenario')}],
        remappings=[
            ('/camera/image_raw', '/camera/color/image_raw'),  # Adjust based on your camera topic
            ('/cmd_vel', '/diff_cont/cmd_vel_unstamped'),     # Adjust based on your robot's cmd_vel topic
        ]
    )
    
    return LaunchDescription([
        scenario_arg,
        competition_node,
    ]) 