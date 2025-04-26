// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_robot_camera_msgs:msg/Detection.idl
// generated code does not contain a copyright notice
#include "my_robot_camera_msgs/msg/detail/detection__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
my_robot_camera_msgs__msg__Detection__init(my_robot_camera_msgs__msg__Detection * msg)
{
  if (!msg) {
    return false;
  }
  // class_id
  // x1
  // y1
  // x2
  // y2
  // confidence
  return true;
}

void
my_robot_camera_msgs__msg__Detection__fini(my_robot_camera_msgs__msg__Detection * msg)
{
  if (!msg) {
    return;
  }
  // class_id
  // x1
  // y1
  // x2
  // y2
  // confidence
}

bool
my_robot_camera_msgs__msg__Detection__are_equal(const my_robot_camera_msgs__msg__Detection * lhs, const my_robot_camera_msgs__msg__Detection * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // class_id
  if (lhs->class_id != rhs->class_id) {
    return false;
  }
  // x1
  if (lhs->x1 != rhs->x1) {
    return false;
  }
  // y1
  if (lhs->y1 != rhs->y1) {
    return false;
  }
  // x2
  if (lhs->x2 != rhs->x2) {
    return false;
  }
  // y2
  if (lhs->y2 != rhs->y2) {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  return true;
}

bool
my_robot_camera_msgs__msg__Detection__copy(
  const my_robot_camera_msgs__msg__Detection * input,
  my_robot_camera_msgs__msg__Detection * output)
{
  if (!input || !output) {
    return false;
  }
  // class_id
  output->class_id = input->class_id;
  // x1
  output->x1 = input->x1;
  // y1
  output->y1 = input->y1;
  // x2
  output->x2 = input->x2;
  // y2
  output->y2 = input->y2;
  // confidence
  output->confidence = input->confidence;
  return true;
}

my_robot_camera_msgs__msg__Detection *
my_robot_camera_msgs__msg__Detection__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__Detection * msg = (my_robot_camera_msgs__msg__Detection *)allocator.allocate(sizeof(my_robot_camera_msgs__msg__Detection), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_robot_camera_msgs__msg__Detection));
  bool success = my_robot_camera_msgs__msg__Detection__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_robot_camera_msgs__msg__Detection__destroy(my_robot_camera_msgs__msg__Detection * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_robot_camera_msgs__msg__Detection__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_robot_camera_msgs__msg__Detection__Sequence__init(my_robot_camera_msgs__msg__Detection__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__Detection * data = NULL;

  if (size) {
    data = (my_robot_camera_msgs__msg__Detection *)allocator.zero_allocate(size, sizeof(my_robot_camera_msgs__msg__Detection), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_robot_camera_msgs__msg__Detection__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_robot_camera_msgs__msg__Detection__fini(&data[i - 1]);
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
my_robot_camera_msgs__msg__Detection__Sequence__fini(my_robot_camera_msgs__msg__Detection__Sequence * array)
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
      my_robot_camera_msgs__msg__Detection__fini(&array->data[i]);
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

my_robot_camera_msgs__msg__Detection__Sequence *
my_robot_camera_msgs__msg__Detection__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__Detection__Sequence * array = (my_robot_camera_msgs__msg__Detection__Sequence *)allocator.allocate(sizeof(my_robot_camera_msgs__msg__Detection__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_robot_camera_msgs__msg__Detection__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_robot_camera_msgs__msg__Detection__Sequence__destroy(my_robot_camera_msgs__msg__Detection__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_robot_camera_msgs__msg__Detection__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_robot_camera_msgs__msg__Detection__Sequence__are_equal(const my_robot_camera_msgs__msg__Detection__Sequence * lhs, const my_robot_camera_msgs__msg__Detection__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_robot_camera_msgs__msg__Detection__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_robot_camera_msgs__msg__Detection__Sequence__copy(
  const my_robot_camera_msgs__msg__Detection__Sequence * input,
  my_robot_camera_msgs__msg__Detection__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_robot_camera_msgs__msg__Detection);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_robot_camera_msgs__msg__Detection * data =
      (my_robot_camera_msgs__msg__Detection *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_robot_camera_msgs__msg__Detection__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_robot_camera_msgs__msg__Detection__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_robot_camera_msgs__msg__Detection__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
