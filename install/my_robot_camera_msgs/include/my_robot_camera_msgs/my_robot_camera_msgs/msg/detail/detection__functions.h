// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from my_robot_camera_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__FUNCTIONS_H_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "my_robot_camera_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "my_robot_camera_msgs/msg/detail/detection__struct.h"

/// Initialize msg/Detection message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * my_robot_camera_msgs__msg__Detection
 * )) before or use
 * my_robot_camera_msgs__msg__Detection__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__init(my_robot_camera_msgs__msg__Detection * msg);

/// Finalize msg/Detection message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
void
my_robot_camera_msgs__msg__Detection__fini(my_robot_camera_msgs__msg__Detection * msg);

/// Create msg/Detection message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * my_robot_camera_msgs__msg__Detection__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
my_robot_camera_msgs__msg__Detection *
my_robot_camera_msgs__msg__Detection__create();

/// Destroy msg/Detection message.
/**
 * It calls
 * my_robot_camera_msgs__msg__Detection__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
void
my_robot_camera_msgs__msg__Detection__destroy(my_robot_camera_msgs__msg__Detection * msg);

/// Check for msg/Detection message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__are_equal(const my_robot_camera_msgs__msg__Detection * lhs, const my_robot_camera_msgs__msg__Detection * rhs);

/// Copy a msg/Detection message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__copy(
  const my_robot_camera_msgs__msg__Detection * input,
  my_robot_camera_msgs__msg__Detection * output);

/// Initialize array of msg/Detection messages.
/**
 * It allocates the memory for the number of elements and calls
 * my_robot_camera_msgs__msg__Detection__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__Sequence__init(my_robot_camera_msgs__msg__Detection__Sequence * array, size_t size);

/// Finalize array of msg/Detection messages.
/**
 * It calls
 * my_robot_camera_msgs__msg__Detection__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
void
my_robot_camera_msgs__msg__Detection__Sequence__fini(my_robot_camera_msgs__msg__Detection__Sequence * array);

/// Create array of msg/Detection messages.
/**
 * It allocates the memory for the array and calls
 * my_robot_camera_msgs__msg__Detection__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
my_robot_camera_msgs__msg__Detection__Sequence *
my_robot_camera_msgs__msg__Detection__Sequence__create(size_t size);

/// Destroy array of msg/Detection messages.
/**
 * It calls
 * my_robot_camera_msgs__msg__Detection__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
void
my_robot_camera_msgs__msg__Detection__Sequence__destroy(my_robot_camera_msgs__msg__Detection__Sequence * array);

/// Check for msg/Detection message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__Sequence__are_equal(const my_robot_camera_msgs__msg__Detection__Sequence * lhs, const my_robot_camera_msgs__msg__Detection__Sequence * rhs);

/// Copy an array of msg/Detection messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_robot_camera_msgs
bool
my_robot_camera_msgs__msg__Detection__Sequence__copy(
  const my_robot_camera_msgs__msg__Detection__Sequence * input,
  my_robot_camera_msgs__msg__Detection__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__FUNCTIONS_H_
