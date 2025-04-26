// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_robot_camera_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Detection in the package my_robot_camera_msgs.
typedef struct my_robot_camera_msgs__msg__Detection
{
  int32_t class_id;
  int32_t x1;
  int32_t y1;
  int32_t x2;
  int32_t y2;
  float confidence;
} my_robot_camera_msgs__msg__Detection;

// Struct for a sequence of my_robot_camera_msgs__msg__Detection.
typedef struct my_robot_camera_msgs__msg__Detection__Sequence
{
  my_robot_camera_msgs__msg__Detection * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_camera_msgs__msg__Detection__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
