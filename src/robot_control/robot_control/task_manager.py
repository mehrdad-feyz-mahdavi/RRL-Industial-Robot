from enum import Enum
from typing import List, Dict, Tuple, Union
import numpy as np

class TaskType(Enum):
    NAV = "nav"
    PICK = "pick"
    PLACE = "place"

class Task:
    def __init__(self, task_type: TaskType, task_data: Union[Tuple[float, float, float], str, int]):
        self.task_type = task_type
        self.task_data = task_data

class TaskManager:
    def __init__(self):
        # Workspace locations (x, y, theta)
        self.workspaces = {
            'ws1': (0.0, 0.0, 0.0),
            'ws2': (0.0, 0.0, 0.0),
            'ws3': (0.0, 0.0, 0.0),
            'ws4': (0.0, 0.0, 0.0),
            'ws5': (0.0, 0.0, 0.0),
            'ws6': (0.0, 0.0, 0.0),
            'ws7': (0.0, 0.0, 0.0),
            'ws8': (0.0, 0.0, 0.0),
            'ws9': (0.0, 0.0, 0.0),
            'ws10': (0.0, 0.0, 0.0),
            'ws11': (0.0, 0.0, 0.0),
            'ws12': (0.0, 0.0, 0.0)
        }
        
        # Object locations and offsets
        self.objects = {
            'bolt': {
                'position': (0.0, 0.0, 0.0),
                'offset_x': 0.0,
                'offset_y': 0.0
            },
            'profile_1': {
                'position': (0.0, 0.0, 0.0),
                'offset_x': 0.0,
                'offset_y': 0.0
            }
        }
        
        # Storage locations
        self.storage = [0, 1, 2]
        
        # Task queue
        self.tasks: List[Task] = []
        self.current_task_index = 0
        
    def add_task(self, task_type: str, task_data: Union[Tuple[float, float, float], str, int]):
        """Add a new task to the queue"""
        task_type_enum = TaskType(task_type.lower())
        self.tasks.append(Task(task_type_enum, task_data))
        
    def get_next_task(self) -> Union[Task, None]:
        """Get the next task from the queue"""
        if self.current_task_index < len(self.tasks):
            task = self.tasks[self.current_task_index]
            self.current_task_index += 1
            return task
        return None
        
    def set_workspace_location(self, workspace_id: str, x: float, y: float, theta: float):
        """Set the location of a workspace"""
        if workspace_id in self.workspaces:
            self.workspaces[workspace_id] = (x, y, theta)
            
    def set_object_location(self, object_id: str, x: float, y: float, theta: float, offset_x: float = 0.0, offset_y: float = 0.0):
        """Set the location of an object"""
        if object_id in self.objects:
            self.objects[object_id]['position'] = (x, y, theta)
            self.objects[object_id]['offset_x'] = offset_x
            self.objects[object_id]['offset_y'] = offset_y
            
    def get_task_pose(self, task: Task) -> Tuple[float, float, float]:
        """Get the target pose for a task"""
        if task.task_type == TaskType.NAV:
            if isinstance(task.task_data, str) and task.task_data in self.workspaces:
                return self.workspaces[task.task_data]
            elif isinstance(task.task_data, tuple):
                return task.task_data
        elif task.task_type == TaskType.PICK:
            if isinstance(task.task_data, str) and task.task_data in self.objects:
                obj = self.objects[task.task_data]
                x, y, theta = obj['position']
                return (x + obj['offset_x'], y + obj['offset_y'], theta)
        elif task.task_type == TaskType.PLACE:
            if isinstance(task.task_data, int) and task.task_data in self.storage:
                # Return the storage location pose
                return self.workspaces[f'ws{task.task_data + 1}']
        return (0.0, 0.0, 0.0)  # Default pose 