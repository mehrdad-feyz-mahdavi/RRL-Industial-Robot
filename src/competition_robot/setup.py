from setuptools import setup

package_name = 'competition_robot'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/config', ['config/competition_params.yaml']),
        ('share/' + package_name + '/launch', ['launch/competition_launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='parsa',
    maintainer_email='parsa@todo.todo',
    description='ROS2 package for robot competition with navigation, object detection, and manipulation capabilities',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'competition_node = competition_robot.competition_node:main',
        ],
    },
)
