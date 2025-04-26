// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_control_interfaces:msg/ArmCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_H_
#define ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ArmCommand in the package robot_control_interfaces.
typedef struct robot_control_interfaces__msg__ArmCommand
{
  /// 1-3 for joints, 4=base, 5=gripper_rotate, 6=gripper_claw
  uint8_t joint_num;
  /// Target position
  int32_t angle;
  /// Movement speed
  uint8_t speed;
} robot_control_interfaces__msg__ArmCommand;

// Struct for a sequence of robot_control_interfaces__msg__ArmCommand.
typedef struct robot_control_interfaces__msg__ArmCommand__Sequence
{
  robot_control_interfaces__msg__ArmCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_control_interfaces__msg__ArmCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_H_
