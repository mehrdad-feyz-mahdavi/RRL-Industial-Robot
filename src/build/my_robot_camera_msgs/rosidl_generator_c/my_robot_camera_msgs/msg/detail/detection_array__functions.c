// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_robot_camera_msgs:msg/DetectionArray.idl
// generated code does not contain a copyright notice
#include "my_robot_camera_msgs/msg/detail/detection_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `detections`
#include "my_robot_camera_msgs/msg/detail/detection__functions.h"

bool
my_robot_camera_msgs__msg__DetectionArray__init(my_robot_camera_msgs__msg__DetectionArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    my_robot_camera_msgs__msg__DetectionArray__fini(msg);
    return false;
  }
  // detections
  if (!my_robot_camera_msgs__msg__Detection__Sequence__init(&msg->detections, 0)) {
    my_robot_camera_msgs__msg__DetectionArray__fini(msg);
    return false;
  }
  return true;
}

void
my_robot_camera_msgs__msg__DetectionArray__fini(my_robot_camera_msgs__msg__DetectionArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // detections
  my_robot_camera_msgs__msg__Detection__Sequence__fini(&msg->detections);
}

bool
my_robot_camera_msgs__msg__DetectionArray__are_equal(const my_robot_camera_msgs__msg__DetectionArray * lhs, const my_robot_camera_msgs__msg__DetectionArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // detections
  if (!my_robot_camera_msgs__msg__Detection__Sequence__are_equal(
      &(lhs->detections), &(rhs->detections)))
  {
    return false;
  }
  return true;
}

bool
my_robot_camera_msgs__msg__DetectionArray__copy(
  const my_robot_camera_msgs__msg__DetectionArray * input,
  my_robot_camera_msgs__msg__DetectionArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // detections
  if (!my_robot_camera_msgs__msg__Detection__Sequence__copy(
      &(input->detections), &(output->detections)))
  {
    return false;
  }
  return true;
}

my_robot_camera_msgs__msg__DetectionArray *
my_robot_camera_msgs__msg__DetectionArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__DetectionArray * msg = (my_robot_camera_msgs__msg__DetectionArray *)allocator.allocate(sizeof(my_robot_camera_msgs__msg__DetectionArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_robot_camera_msgs__msg__DetectionArray));
  bool success = my_robot_camera_msgs__msg__DetectionArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_robot_camera_msgs__msg__DetectionArray__destroy(my_robot_camera_msgs__msg__DetectionArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_robot_camera_msgs__msg__DetectionArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_robot_camera_msgs__msg__DetectionArray__Sequence__init(my_robot_camera_msgs__msg__DetectionArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__DetectionArray * data = NULL;

  if (size) {
    data = (my_robot_camera_msgs__msg__DetectionArray *)allocator.zero_allocate(size, sizeof(my_robot_camera_msgs__msg__DetectionArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_robot_camera_msgs__msg__DetectionArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_robot_camera_msgs__msg__DetectionArray__fini(&data[i - 1]);
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
my_robot_camera_msgs__msg__DetectionArray__Sequence__fini(my_robot_camera_msgs__msg__DetectionArray__Sequence * array)
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
      my_robot_camera_msgs__msg__DetectionArray__fini(&array->data[i]);
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

my_robot_camera_msgs__msg__DetectionArray__Sequence *
my_robot_camera_msgs__msg__DetectionArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_camera_msgs__msg__DetectionArray__Sequence * array = (my_robot_camera_msgs__msg__DetectionArray__Sequence *)allocator.allocate(sizeof(my_robot_camera_msgs__msg__DetectionArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_robot_camera_msgs__msg__DetectionArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_robot_camera_msgs__msg__DetectionArray__Sequence__destroy(my_robot_camera_msgs__msg__DetectionArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_robot_camera_msgs__msg__DetectionArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_robot_camera_msgs__msg__DetectionArray__Sequence__are_equal(const my_robot_camera_msgs__msg__DetectionArray__Sequence * lhs, const my_robot_camera_msgs__msg__DetectionArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_robot_camera_msgs__msg__DetectionArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_robot_camera_msgs__msg__DetectionArray__Sequence__copy(
  const my_robot_camera_msgs__msg__DetectionArray__Sequence * input,
  my_robot_camera_msgs__msg__DetectionArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_robot_camera_msgs__msg__DetectionArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_robot_camera_msgs__msg__DetectionArray * data =
      (my_robot_camera_msgs__msg__DetectionArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_robot_camera_msgs__msg__DetectionArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_robot_camera_msgs__msg__DetectionArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_robot_camera_msgs__msg__DetectionArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
