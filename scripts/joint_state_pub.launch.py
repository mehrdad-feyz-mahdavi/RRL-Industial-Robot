from launch import LaunchDescription
   from launch_ros.actions import Node

   def generate_launch_description():
       return LaunchDescription([
           Node(
               package='your_package',
               executable='joint_state_publisher.py',
               output='screen'
           )
       ])
