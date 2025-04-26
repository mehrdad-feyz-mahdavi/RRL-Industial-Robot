import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # مسیر فایل پیکربندی
    pkg_dir = get_package_share_directory('navigation_config')
    amcl_config = os.path.join(pkg_dir, 'config', 'amcl_config.yaml')

    # نود AMCL
    amcl_node = Node(
        package='nav2_amcl',
        executable='amcl',
        name='amcl',
        output='screen',
        parameters=[amcl_config],
        remappings=[('scan', '/scan')]  # مطمئن شوید topic اسکن ربات شما را subscribe می‌کند
    )

    # نود Lifecycle Manager
    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_localization',
        output='screen',
        parameters=[{'autostart': True},
                    {'node_names': ['amcl']}]
    )

    return LaunchDescription([
        amcl_node,
        lifecycle_manager
    ])