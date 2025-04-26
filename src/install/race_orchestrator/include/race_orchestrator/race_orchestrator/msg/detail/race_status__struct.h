// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_H_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_H_

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
// Member 'robot_id'
// Member 'current_object'
// Member 'failure_reason'
#include "rosidl_runtime_c/string.h"
// Member 'current_position'
// Member 'next_checkpoint'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/RaceStatus in the package race_orchestrator.
/**
  * Race status information
 */
typedef struct race_orchestrator__msg__RaceStatus
{
  rosidl_runtime_c__String race_id;
  rosidl_runtime_c__String robot_id;
  float current_time;
  float remaining_time;
  /// Current object being collected
  rosidl_runtime_c__String current_object;
  int32_t objects_collected;
  int32_t total_objects;
  rosidl_runtime_c__float__Sequence current_position;
  rosidl_runtime_c__float__Sequence next_checkpoint;
  bool race_completed;
  bool race_failed;
  rosidl_runtime_c__String failure_reason;
} race_orchestrator__msg__RaceStatus;

// Struct for a sequence of race_orchestrator__msg__RaceStatus.
typedef struct race_orchestrator__msg__RaceStatus__Sequence
{
  race_orchestrator__msg__RaceStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} race_orchestrator__msg__RaceStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_H_
