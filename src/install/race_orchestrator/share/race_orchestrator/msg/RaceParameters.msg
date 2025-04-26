# Race configuration parameters
string race_id
string[] object_sequence  # Ordered list of objects to collect
float32 time_limit  # Maximum time allowed for the race
float32[] checkpoints  # Array of checkpoint positions [x1,y1,z1, x2,y2,z2, ...]
bool enable_obstacles  # Whether to enable dynamic obstacles
float32 obstacle_density  # Density of obstacles (0.0 to 1.0)
float32[] start_position  # [x,y,z] starting position
float32[] goal_position  # [x,y,z] goal position 