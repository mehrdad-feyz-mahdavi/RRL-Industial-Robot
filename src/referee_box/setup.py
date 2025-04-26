from setuptools import setup

package_name = 'referee_box'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/config',
            ['referee_box/config/referee_config.yaml']),
        ('share/' + package_name + '/launch',
            ['launch/referee_box.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='parsa',
    maintainer_email='parsa@todo.todo',
    description='RoboCup @Work 2024 Referee Box System',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'referee_box_node = referee_box.referee_box_node:main',
        ],
    },
)
