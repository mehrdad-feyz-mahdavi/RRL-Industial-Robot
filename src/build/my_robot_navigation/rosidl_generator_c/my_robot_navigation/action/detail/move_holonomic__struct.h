// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_robot_navigation:action/MoveHolonomic.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__STRUCT_H_
#define MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target_position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_Goal
{
  geometry_msgs__msg__Point target_position;
  float max_velocity;
} my_robot_navigation__action__MoveHolonomic_Goal;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_Goal.
typedef struct my_robot_navigation__action__MoveHolonomic_Goal__Sequence
{
  my_robot_navigation__action__MoveHolonomic_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_Result
{
  bool success;
  rosidl_runtime_c__String message;
} my_robot_navigation__action__MoveHolonomic_Result;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_Result.
typedef struct my_robot_navigation__action__MoveHolonomic_Result__Sequence
{
  my_robot_navigation__action__MoveHolonomic_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'current_pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_Feedback
{
  float distance_remaining;
  geometry_msgs__msg__Pose current_pose;
} my_robot_navigation__action__MoveHolonomic_Feedback;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_Feedback.
typedef struct my_robot_navigation__action__MoveHolonomic_Feedback__Sequence
{
  my_robot_navigation__action__MoveHolonomic_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "my_robot_navigation/action/detail/move_holonomic__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  my_robot_navigation__action__MoveHolonomic_Goal goal;
} my_robot_navigation__action__MoveHolonomic_SendGoal_Request;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_SendGoal_Request.
typedef struct my_robot_navigation__action__MoveHolonomic_SendGoal_Request__Sequence
{
  my_robot_navigation__action__MoveHolonomic_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} my_robot_navigation__action__MoveHolonomic_SendGoal_Response;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_SendGoal_Response.
typedef struct my_robot_navigation__action__MoveHolonomic_SendGoal_Response__Sequence
{
  my_robot_navigation__action__MoveHolonomic_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} my_robot_navigation__action__MoveHolonomic_GetResult_Request;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_GetResult_Request.
typedef struct my_robot_navigation__action__MoveHolonomic_GetResult_Request__Sequence
{
  my_robot_navigation__action__MoveHolonomic_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "my_robot_navigation/action/detail/move_holonomic__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_GetResult_Response
{
  int8_t status;
  my_robot_navigation__action__MoveHolonomic_Result result;
} my_robot_navigation__action__MoveHolonomic_GetResult_Response;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_GetResult_Response.
typedef struct my_robot_navigation__action__MoveHolonomic_GetResult_Response__Sequence
{
  my_robot_navigation__action__MoveHolonomic_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "my_robot_navigation/action/detail/move_holonomic__struct.h"

/// Struct defined in action/MoveHolonomic in the package my_robot_navigation.
typedef struct my_robot_navigation__action__MoveHolonomic_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  my_robot_navigation__action__MoveHolonomic_Feedback feedback;
} my_robot_navigation__action__MoveHolonomic_FeedbackMessage;

// Struct for a sequence of my_robot_navigation__action__MoveHolonomic_FeedbackMessage.
typedef struct my_robot_navigation__action__MoveHolonomic_FeedbackMessage__Sequence
{
  my_robot_navigation__action__MoveHolonomic_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_navigation__action__MoveHolonomic_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__STRUCT_H_
