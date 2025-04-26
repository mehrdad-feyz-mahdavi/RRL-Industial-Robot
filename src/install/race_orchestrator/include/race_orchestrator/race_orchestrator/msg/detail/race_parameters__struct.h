// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_H_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'race_id'
// Member 'object_sequence'
#include "rosidl_runtime_c/string.h"
// Member 'checkpoints'
// Member 'start_position'
// Member 'goal_position'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/RaceParameters in the package race_orchestrator.
/**
  * Race configuration parameters
 */
typedef struct race_orchestrator__msg__RaceParameters
{
  rosidl_runtime_c__String race_id;
  /// Ordered list of objects to collect
  rosidl_runtime_c__String__Sequence object_sequence;
  /// Maximum time allowed for the race
  float time_limit;
  /// Array of checkpoint positions [x1,y1,z1, x2,y2,z2, ...]
  rosidl_runtime_c__float__Sequence checkpoints;
  /// Whether to enable dynamic obstacles
  bool enable_obstacles;
  /// Density of obstacles (0.0 to 1.0)
  float obstacle_density;
  /// [x,y,z] starting position
  rosidl_runtime_c__float__Sequence start_position;
  /// [x,y,z] goal position
  rosidl_runtime_c__float__Sequence goal_position;
} race_orchestrator__msg__RaceParameters;

// Struct for a sequence of race_orchestrator__msg__RaceParameters.
typedef struct race_orchestrator__msg__RaceParameters__Sequence
{
  race_orchestrator__msg__RaceParameters * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} race_orchestrator__msg__RaceParameters__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_H_
