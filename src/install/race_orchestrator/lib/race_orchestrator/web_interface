#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from flask import Flask, render_template, jsonify, request
from std_msgs.msg import String
from race_orchestrator.msg import RaceStatus
import threading
import json
from typing import Dict
import os

class WebInterface(Node):
    def __init__(self):
        super().__init__('web_interface')
        
        # ROS2 setup
        self.publisher = self.create_publisher(String, '/race/start', 10)
        self.stop_publisher = self.create_publisher(String, '/race/stop', 10)
        self.create_subscription(RaceStatus, '/race/status', 
                               self.status_callback, 10)
        
        # Flask setup
        self.app = Flask(__name__, 
                        template_folder=os.path.join(os.path.dirname(__file__), 
                                                   '../templates'))
        self.race_status: Dict[str, RaceStatus] = {}
        
        # Define routes
        self.app.route('/')(self.index)
        self.app.route('/api/status')(self.get_status)
        self.app.route('/api/start', methods=['POST'])(self.start_race)
        self.app.route('/api/stop/<race_id>', methods=['POST'])(self.stop_race)
        
        # Start Flask in a separate thread
        self.flask_thread = threading.Thread(target=self.run_flask)
        self.flask_thread.daemon = True
        self.flask_thread.start()
        
        self.get_logger().info('Web Interface initialized')

    def run_flask(self):
        self.app.run(host='0.0.0.0', port=5000)

    def index(self):
        return render_template('index.html')

    def get_status(self):
        return jsonify({
            race_id: {
                'current_time': status.current_time,
                'remaining_time': status.remaining_time,
                'objects_collected': status.objects_collected,
                'total_objects': status.total_objects,
                'current_object': status.current_object,
                'race_completed': status.race_completed,
                'race_failed': status.race_failed,
                'failure_reason': status.failure_reason
            }
            for race_id, status in self.race_status.items()
        })

    def start_race(self):
        try:
            config = request.json
            msg = String()
            msg.data = json.dumps(config)
            self.publisher.publish(msg)
            return jsonify({'success': True, 'race_id': config['race_id']})
        except Exception as e:
            return jsonify({'success': False, 'error': str(e)})

    def stop_race(self, race_id):
        try:
            msg = String()
            msg.data = race_id
            self.stop_publisher.publish(msg)
            return jsonify({'success': True})
        except Exception as e:
            return jsonify({'success': False, 'error': str(e)})

    def status_callback(self, msg):
        self.race_status[msg.race_id] = msg

def main(args=None):
    rclpy.init(args=args)
    web_interface = WebInterface()
    rclpy.spin(web_interface)
    web_interface.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 