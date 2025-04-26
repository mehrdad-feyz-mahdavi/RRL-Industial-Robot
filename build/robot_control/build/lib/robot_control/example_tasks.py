import rclpy
from robot_control.robot_server import MecanumController
from robot_control.task_manager import TaskManager

def main():
    rclpy.init()
    
    # Create the robot controller
    robot = MecanumController()
    
    try:
        # Set workspace locations (example values)
        robot.task_manager.set_workspace_location('ws1', 2.1, -0.65, -1.9)
        robot.task_manager.set_workspace_location('ws3', 3.14, 0.33, -0.4)
        
        # Set object locations (example values)
        robot.task_manager.set_object_location('bolt', 0.9, 0.7, 1.07, 0.1, 0.1)
        
        # Add tasks to the queue
        robot.task_manager.add_task('nav', 'ws1')  # Navigate to workspace 1
        robot.task_manager.add_task('pick', 'bolt')  # Pick up the bolt
        robot.task_manager.add_task('nav', 'ws3')  # Navigate to workspace 3
        robot.task_manager.add_task('place', 0)  # Place in storage 0
        
        # Run the robot
        rclpy.spin(robot)
        
    except KeyboardInterrupt:
        pass
    finally:
        robot.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 