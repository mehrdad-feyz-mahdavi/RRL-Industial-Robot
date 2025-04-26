#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from race_orchestrator.msg import RaceParameters, RaceStatus
import time
import json
from typing import Dict, List

class RaceManager(Node):
    def __init__(self):
        super().__init__('race_manager')
        
        # Publishers
        self.parameters_pub = self.create_publisher(
            RaceParameters, '/race/parameters', 10)
        self.status_pub = self.create_publisher(
            RaceStatus, '/race/status', 10)
        
        # Subscribers
        self.create_subscription(
            String, '/race/start', self.start_race_callback, 10)
        self.create_subscription(
            String, '/race/stop', self.stop_race_callback, 10)
        
        # Race state
        self.active_races: Dict[str, Dict] = {}
        self.timer = self.create_timer(0.1, self.update_race_status)
        
        self.get_logger().info('Race Manager initialized')

    def start_race_callback(self, msg):
        try:
            config = json.loads(msg.data)
            race_id = config.get('race_id')
            
            if race_id in self.active_races:
                self.get_logger().warn(f'Race {race_id} already active')
                return
            
            # Create new race entry
            self.active_races[race_id] = {
                'start_time': time.time(),
                'config': config,
                'status': {
                    'objects_collected': 0,
                    'current_object_index': 0,
                    'completed': False,
                    'failed': False
                }
            }
            
            # Publish race parameters
            params = RaceParameters()
            params.race_id = race_id
            params.object_sequence = config['object_sequence']
            params.time_limit = config['time_limit']
            params.checkpoints = config['checkpoints']
            params.enable_obstacles = config.get('enable_obstacles', False)
            params.obstacle_density = config.get('obstacle_density', 0.0)
            params.start_position = config['start_position']
            params.goal_position = config['goal_position']
            
            self.parameters_pub.publish(params)
            self.get_logger().info(f'Started race {race_id}')
            
        except Exception as e:
            self.get_logger().error(f'Error starting race: {str(e)}')

    def stop_race_callback(self, msg):
        race_id = msg.data
        if race_id in self.active_races:
            del self.active_races[race_id]
            self.get_logger().info(f'Stopped race {race_id}')

    def update_race_status(self):
        current_time = time.time()
        
        for race_id, race_data in self.active_races.items():
            elapsed_time = current_time - race_data['start_time']
            remaining_time = race_data['config']['time_limit'] - elapsed_time
            
            if remaining_time <= 0:
                race_data['status']['failed'] = True
                race_data['status']['failure_reason'] = 'Time limit exceeded'
            
            status = RaceStatus()
            status.race_id = race_id
            status.current_time = elapsed_time
            status.remaining_time = remaining_time
            status.objects_collected = race_data['status']['objects_collected']
            status.total_objects = len(race_data['config']['object_sequence'])
            status.current_object = race_data['config']['object_sequence'][
                race_data['status']['current_object_index']]
            status.race_completed = race_data['status']['completed']
            status.race_failed = race_data['status']['failed']
            status.failure_reason = race_data['status'].get('failure_reason', '')
            
            self.status_pub.publish(status)

def main(args=None):
    rclpy.init(args=args)
    race_manager = RaceManager()
    rclpy.spin(race_manager)
    race_manager.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 