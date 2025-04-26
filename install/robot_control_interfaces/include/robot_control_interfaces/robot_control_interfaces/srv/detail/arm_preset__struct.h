// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_control_interfaces:srv/ArmPreset.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_H_
#define ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ArmPreset in the package robot_control_interfaces.
typedef struct robot_control_interfaces__srv__ArmPreset_Request
{
  /// 1=Home, 2=Extended, 3=Camera vertical
  uint8_t preset_num;
} robot_control_interfaces__srv__ArmPreset_Request;

// Struct for a sequence of robot_control_interfaces__srv__ArmPreset_Request.
typedef struct robot_control_interfaces__srv__ArmPreset_Request__Sequence
{
  robot_control_interfaces__srv__ArmPreset_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_control_interfaces__srv__ArmPreset_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ArmPreset in the package robot_control_interfaces.
typedef struct robot_control_interfaces__srv__ArmPreset_Response
{
  bool success;
  rosidl_runtime_c__String message;
} robot_control_interfaces__srv__ArmPreset_Response;

// Struct for a sequence of robot_control_interfaces__srv__ArmPreset_Response.
typedef struct robot_control_interfaces__srv__ArmPreset_Response__Sequence
{
  robot_control_interfaces__srv__ArmPreset_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_control_interfaces__srv__ArmPreset_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_H_
