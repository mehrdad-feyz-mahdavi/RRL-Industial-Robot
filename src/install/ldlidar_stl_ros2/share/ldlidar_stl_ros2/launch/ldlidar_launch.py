#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    ld = LaunchDescription()

    # Get the path to the package
    pkg_dir = get_package_share_directory('ldlidar_stl_ros2')
    
    # Path to the laser filter config file
    laser_filter_config = os.path.join(pkg_dir, 'config', 'laser_filter_config.yaml')

    laser_filter_node = Node(
        package="laser_filters",
        executable="scan_to_scan_filter_chain",
        parameters=[laser_filter_config],
        remappings=[
            ('scan', 'scan_raw'),
            ('scan_filtered', 'scan')
        ]
    )
    ld.add_action(laser_filter_node)

    # 3. TF Node (fixed typo)
    base_link_to_laser_tf_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0', '0', '0.2', '0', '0', '0', 'base_link', 'laser']
    )
    ld.add_action(base_link_to_laser_tf_node)

    return ld