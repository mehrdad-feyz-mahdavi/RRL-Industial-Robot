// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__FUNCTIONS_H_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "race_orchestrator/msg/rosidl_generator_c__visibility_control.h"

#include "race_orchestrator/msg/detail/race_status__struct.h"

/// Initialize msg/RaceStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * race_orchestrator__msg__RaceStatus
 * )) before or use
 * race_orchestrator__msg__RaceStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__init(race_orchestrator__msg__RaceStatus * msg);

/// Finalize msg/RaceStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
void
race_orchestrator__msg__RaceStatus__fini(race_orchestrator__msg__RaceStatus * msg);

/// Create msg/RaceStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * race_orchestrator__msg__RaceStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
race_orchestrator__msg__RaceStatus *
race_orchestrator__msg__RaceStatus__create();

/// Destroy msg/RaceStatus message.
/**
 * It calls
 * race_orchestrator__msg__RaceStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
void
race_orchestrator__msg__RaceStatus__destroy(race_orchestrator__msg__RaceStatus * msg);

/// Check for msg/RaceStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__are_equal(const race_orchestrator__msg__RaceStatus * lhs, const race_orchestrator__msg__RaceStatus * rhs);

/// Copy a msg/RaceStatus message.
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
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__copy(
  const race_orchestrator__msg__RaceStatus * input,
  race_orchestrator__msg__RaceStatus * output);

/// Initialize array of msg/RaceStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * race_orchestrator__msg__RaceStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__Sequence__init(race_orchestrator__msg__RaceStatus__Sequence * array, size_t size);

/// Finalize array of msg/RaceStatus messages.
/**
 * It calls
 * race_orchestrator__msg__RaceStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
void
race_orchestrator__msg__RaceStatus__Sequence__fini(race_orchestrator__msg__RaceStatus__Sequence * array);

/// Create array of msg/RaceStatus messages.
/**
 * It allocates the memory for the array and calls
 * race_orchestrator__msg__RaceStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
race_orchestrator__msg__RaceStatus__Sequence *
race_orchestrator__msg__RaceStatus__Sequence__create(size_t size);

/// Destroy array of msg/RaceStatus messages.
/**
 * It calls
 * race_orchestrator__msg__RaceStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
void
race_orchestrator__msg__RaceStatus__Sequence__destroy(race_orchestrator__msg__RaceStatus__Sequence * array);

/// Check for msg/RaceStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__Sequence__are_equal(const race_orchestrator__msg__RaceStatus__Sequence * lhs, const race_orchestrator__msg__RaceStatus__Sequence * rhs);

/// Copy an array of msg/RaceStatus messages.
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
ROSIDL_GENERATOR_C_PUBLIC_race_orchestrator
bool
race_orchestrator__msg__RaceStatus__Sequence__copy(
  const race_orchestrator__msg__RaceStatus__Sequence * input,
  race_orchestrator__msg__RaceStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__FUNCTIONS_H_
