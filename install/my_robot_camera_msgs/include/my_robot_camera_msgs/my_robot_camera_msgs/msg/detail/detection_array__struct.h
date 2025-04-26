// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_robot_camera_msgs:msg/DetectionArray.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'detections'
#include "my_robot_camera_msgs/msg/detail/detection__struct.h"

/// Struct defined in msg/DetectionArray in the package my_robot_camera_msgs.
typedef struct my_robot_camera_msgs__msg__DetectionArray
{
  std_msgs__msg__Header header;
  my_robot_camera_msgs__msg__Detection__Sequence detections;
} my_robot_camera_msgs__msg__DetectionArray;

// Struct for a sequence of my_robot_camera_msgs__msg__DetectionArray.
typedef struct my_robot_camera_msgs__msg__DetectionArray__Sequence
{
  my_robot_camera_msgs__msg__DetectionArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_camera_msgs__msg__DetectionArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_
