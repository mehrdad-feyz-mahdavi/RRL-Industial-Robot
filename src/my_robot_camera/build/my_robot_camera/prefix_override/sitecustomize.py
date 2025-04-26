import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/parsa/main_robot_ws/src/my_robot_camera/install/my_robot_camera'
