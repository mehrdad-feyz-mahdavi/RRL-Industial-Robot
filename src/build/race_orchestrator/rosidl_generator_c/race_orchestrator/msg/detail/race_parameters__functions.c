// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice
#include "race_orchestrator/msg/detail/race_parameters__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `race_id`
// Member `object_sequence`
#include "rosidl_runtime_c/string_functions.h"
// Member `checkpoints`
// Member `start_position`
// Member `goal_position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
race_orchestrator__msg__RaceParameters__init(race_orchestrator__msg__RaceParameters * msg)
{
  if (!msg) {
    return false;
  }
  // race_id
  if (!rosidl_runtime_c__String__init(&msg->race_id)) {
    race_orchestrator__msg__RaceParameters__fini(msg);
    return false;
  }
  // object_sequence
  if (!rosidl_runtime_c__String__Sequence__init(&msg->object_sequence, 0)) {
    race_orchestrator__msg__RaceParameters__fini(msg);
    return false;
  }
  // time_limit
  // checkpoints
  if (!rosidl_runtime_c__float__Sequence__init(&msg->checkpoints, 0)) {
    race_orchestrator__msg__RaceParameters__fini(msg);
    return false;
  }
  // enable_obstacles
  // obstacle_density
  // start_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->start_position, 0)) {
    race_orchestrator__msg__RaceParameters__fini(msg);
    return false;
  }
  // goal_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->goal_position, 0)) {
    race_orchestrator__msg__RaceParameters__fini(msg);
    return false;
  }
  return true;
}

void
race_orchestrator__msg__RaceParameters__fini(race_orchestrator__msg__RaceParameters * msg)
{
  if (!msg) {
    return;
  }
  // race_id
  rosidl_runtime_c__String__fini(&msg->race_id);
  // object_sequence
  rosidl_runtime_c__String__Sequence__fini(&msg->object_sequence);
  // time_limit
  // checkpoints
  rosidl_runtime_c__float__Sequence__fini(&msg->checkpoints);
  // enable_obstacles
  // obstacle_density
  // start_position
  rosidl_runtime_c__float__Sequence__fini(&msg->start_position);
  // goal_position
  rosidl_runtime_c__float__Sequence__fini(&msg->goal_position);
}

bool
race_orchestrator__msg__RaceParameters__are_equal(const race_orchestrator__msg__RaceParameters * lhs, const race_orchestrator__msg__RaceParameters * rhs)
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
  // object_sequence
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->object_sequence), &(rhs->object_sequence)))
  {
    return false;
  }
  // time_limit
  if (lhs->time_limit != rhs->time_limit) {
    return false;
  }
  // checkpoints
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->checkpoints), &(rhs->checkpoints)))
  {
    return false;
  }
  // enable_obstacles
  if (lhs->enable_obstacles != rhs->enable_obstacles) {
    return false;
  }
  // obstacle_density
  if (lhs->obstacle_density != rhs->obstacle_density) {
    return false;
  }
  // start_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->start_position), &(rhs->start_position)))
  {
    return false;
  }
  // goal_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->goal_position), &(rhs->goal_position)))
  {
    return false;
  }
  return true;
}

bool
race_orchestrator__msg__RaceParameters__copy(
  const race_orchestrator__msg__RaceParameters * input,
  race_orchestrator__msg__RaceParameters * output)
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
  // object_sequence
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->object_sequence), &(output->object_sequence)))
  {
    return false;
  }
  // time_limit
  output->time_limit = input->time_limit;
  // checkpoints
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->checkpoints), &(output->checkpoints)))
  {
    return false;
  }
  // enable_obstacles
  output->enable_obstacles = input->enable_obstacles;
  // obstacle_density
  output->obstacle_density = input->obstacle_density;
  // start_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->start_position), &(output->start_position)))
  {
    return false;
  }
  // goal_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->goal_position), &(output->goal_position)))
  {
    return false;
  }
  return true;
}

race_orchestrator__msg__RaceParameters *
race_orchestrator__msg__RaceParameters__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceParameters * msg = (race_orchestrator__msg__RaceParameters *)allocator.allocate(sizeof(race_orchestrator__msg__RaceParameters), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(race_orchestrator__msg__RaceParameters));
  bool success = race_orchestrator__msg__RaceParameters__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
race_orchestrator__msg__RaceParameters__destroy(race_orchestrator__msg__RaceParameters * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    race_orchestrator__msg__RaceParameters__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
race_orchestrator__msg__RaceParameters__Sequence__init(race_orchestrator__msg__RaceParameters__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceParameters * data = NULL;

  if (size) {
    data = (race_orchestrator__msg__RaceParameters *)allocator.zero_allocate(size, sizeof(race_orchestrator__msg__RaceParameters), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = race_orchestrator__msg__RaceParameters__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        race_orchestrator__msg__RaceParameters__fini(&data[i - 1]);
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
race_orchestrator__msg__RaceParameters__Sequence__fini(race_orchestrator__msg__RaceParameters__Sequence * array)
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
      race_orchestrator__msg__RaceParameters__fini(&array->data[i]);
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

race_orchestrator__msg__RaceParameters__Sequence *
race_orchestrator__msg__RaceParameters__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  race_orchestrator__msg__RaceParameters__Sequence * array = (race_orchestrator__msg__RaceParameters__Sequence *)allocator.allocate(sizeof(race_orchestrator__msg__RaceParameters__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = race_orchestrator__msg__RaceParameters__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
race_orchestrator__msg__RaceParameters__Sequence__destroy(race_orchestrator__msg__RaceParameters__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    race_orchestrator__msg__RaceParameters__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
race_orchestrator__msg__RaceParameters__Sequence__are_equal(const race_orchestrator__msg__RaceParameters__Sequence * lhs, const race_orchestrator__msg__RaceParameters__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!race_orchestrator__msg__RaceParameters__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
race_orchestrator__msg__RaceParameters__Sequence__copy(
  const race_orchestrator__msg__RaceParameters__Sequence * input,
  race_orchestrator__msg__RaceParameters__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(race_orchestrator__msg__RaceParameters);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    race_orchestrator__msg__RaceParameters * data =
      (race_orchestrator__msg__RaceParameters *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!race_orchestrator__msg__RaceParameters__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          race_orchestrator__msg__RaceParameters__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!race_orchestrator__msg__RaceParameters__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
