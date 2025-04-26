// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice
#include "race_orchestrator/msg/detail/race_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `race_id`
// Member `robot_id`
// Member `current_object`
// Member `failure_reason`
#include "rosidl_runtime_c/string_functions.h"
// Member `current_position`
// Member `next_checkpoint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
race_orchestrator__msg__RaceStatus__init(race_orchestrator__msg__RaceStatus * msg)
{
  if (!msg) {
    return false;
  }
  // race_id
  if (!rosidl_runtime_c__String__init(&msg->race_id)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__init(&msg->robot_id)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  // current_time
  // remaining_time
  // current_object
  if (!rosidl_runtime_c__String__init(&msg->current_object)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  // objects_collected
  // total_objects
  // current_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->current_position, 0)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  // next_checkpoint
  if (!rosidl_runtime_c__float__Sequence__init(&msg->next_checkpoint, 0)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  // race_completed
  // race_failed
  // failure_reason
  if (!rosidl_runtime_c__String__init(&msg->failure_reason)) {
    race_orchestrator__msg__RaceStatus__fini(msg);
    return false;
  }
  return true;
}

void
race_orchestrator__msg__RaceStatus__fini(race_orchestrator__msg__RaceStatus * msg)
{
  if (!msg) {
    return;
  }
  // race_id
  rosidl_runtime_c__String__fini(&msg->race_id);
  // robot_id
  rosidl_runtime_c__String__fini(&msg->robot_id);
  // current_time
  // remaining_time
  // current_object
  rosidl_runtime_c__String__fini(&msg->current_object);
  // objects_collected
  // total_objects
  // current_position
  rosidl_runtime_c__float__Sequence__fini(&msg->current_position);
  // next_checkpoint
  rosidl_runtime_c__float__Sequence__fini(&msg->next_checkpoint);
  // race_completed
  // race_failed
  // failure_reason
  rosidl_runtime_c__String__fini(&msg->failure_reason);
}

bool
race_orchestrator__msg__RaceStatus__are_equal(const race_orchestrator__msg__RaceStatus * lhs, const race_orchestrator__msg__RaceStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // race_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->race_id), &(rhs->race_id)))
  {
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_id), &(rhs->robot_id)))
  {
    return false;
  }
  // current_time
  if (lhs->current_time != rhs->current_time) {
    return false;
  }
  // remaining_time
  if (lhs->remaining_time != rhs->remaining_time) {
    return false;
  }
  // current_object
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->current_object), &(rhs->current_object)))
  {
    return false;
  }
  // objects_collected
  if (lhs->objects_collected != rhs->objects_collected) {
    return false;
  }
  // total_objects
  if (lhs->total_objects != rhs->total_objects) {
    return false;
  }
  // current_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->current_position), &(rhs->current_position)))
  {
    return false;
  }
  // next_checkpoint
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->next_checkpoint), &(rhs->next_checkpoint)))
  {
    return false;
  }
  // race_completed
  if (lhs->race_completed != rhs->race_completed) {
    return false;
  }
  // race_failed
  if (lhs->race_failed != rhs->race_failed) {
    return false;
  }
  // failure_reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->failure_reason), &(rhs->failure_reason)))
  {
    return false;
  }
  return true;
}

bool
race_orchestrator__msg__RaceStatus__copy(
  const race_orchestrator__msg__RaceStatus * input,
  race_orchestrator__msg__RaceStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // race_id
  if (!rosidl_runtime_c__String__copy(
      &(input->race_id), &(output->race_id)))
  {
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_id), &(output->robot_id)))
  {
    return false;
  }
  // current_time
  output->current_time = input->current_time;
  // remaining_time
  output->remaining_time = input->remaining_time;
  // current_object
  if (!rosidl_runtime_c__String__copy(
      &(input->current_object), &(output->current_object)))
  {
    return false;
  }
  // objects_collected
  output->objects_collected = input->objects_collected;
  // total_objects
  output->total_objects = input->total_objects;
  // current_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->current_position), &(output->current_position)))
  {
    return false;
  }
  // next_checkpoint
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->next_checkpoint), &(output->next_checkpoint)))
  {
    return false;
  }
  // race_completed
  output->race_completed = input->race_completed;
  // race_failed
  output->race_failed = input->race_failed;
  // failure_reason
  if (!rosidl_runtime_c__String__copy(
      &(input->failure_reason), &(output->failure_reason)))
  {
    return false;
  }
  return true;
}

race_orchestrator__msg__RaceStatus *
race_orchestrator__msg__RaceStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceStatus * msg = (race_orchestrator__msg__RaceStatus *)allocator.allocate(sizeof(race_orchestrator__msg__RaceStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(race_orchestrator__msg__RaceStatus));
  bool success = race_orchestrator__msg__RaceStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
race_orchestrator__msg__RaceStatus__destroy(race_orchestrator__msg__RaceStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    race_orchestrator__msg__RaceStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
race_orchestrator__msg__RaceStatus__Sequence__init(race_orchestrator__msg__RaceStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceStatus * data = NULL;

  if (size) {
    data = (race_orchestrator__msg__RaceStatus *)allocator.zero_allocate(size, sizeof(race_orchestrator__msg__RaceStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = race_orchestrator__msg__RaceStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        race_orchestrator__msg__RaceStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
race_orchestrator__msg__RaceStatus__Sequence__fini(race_orchestrator__msg__RaceStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      race_orchestrator__msg__RaceStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

race_orchestrator__msg__RaceStatus__Sequence *
race_orchestrator__msg__RaceStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceStatus__Sequence * array = (race_orchestrator__msg__RaceStatus__Sequence *)allocator.allocate(sizeof(race_orchestrator__msg__RaceStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = race_orchestrator__msg__RaceStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
race_orchestrator__msg__RaceStatus__Sequence__destroy(race_orchestrator__msg__RaceStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    race_orchestrator__msg__RaceStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
race_orchestrator__msg__RaceStatus__Sequence__are_equal(const race_orchestrator__msg__RaceStatus__Sequence * lhs, const race_orchestrator__msg__RaceStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!race_orchestrator__msg__RaceStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
race_orchestrator__msg__RaceStatus__Sequence__copy(
  const race_orchestrator__msg__RaceStatus__Sequence * input,
  race_orchestrator__msg__RaceStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(race_orchestrator__msg__RaceStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    race_orchestrator__msg__RaceStatus * data =
      (race_orchestrator__msg__RaceStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!race_orchestrator__msg__RaceStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          race_orchestrator__msg__RaceStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!race_orchestrator__msg__RaceStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
