from setuptools import setup
import os
from glob import glob

package_name = 'robot_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), 
            glob(os.path.join(package_name, 'launch', '*.launch.py'))),
        (os.path.join('share', package_name, 'config'), 
            glob(os.path.join(package_name, 'config', '*.yaml'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='user',
    maintainer_email='user@todo.todo',
    description='ROS 2 node for controlling a custom robotic arm via socket communication',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'arm_controller_node = robot_control.arm_controller_node:main',
            'arm_server = robot_control.arm_server:main',
            'robot_server = robot_control.robot_server:main',
            'old_robot_server = robot_control.old_robot_server:main',
            'arm_gui = robot_control.arm_gui:main',
            'arm_driver_node = robot_control.arm_driver_node:main',
        ],
    },
)