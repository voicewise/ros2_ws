// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice
#include "puppy_control_msgs/msg/detail/pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
puppy_control_msgs__msg__Pose__init(puppy_control_msgs__msg__Pose * msg)
{
  if (!msg) {
    return false;
  }
  // roll
  // pitch
  // yaw
  // height
  // x_shift
  // stance_x
  // stance_y
  // run_time
  return true;
}

void
puppy_control_msgs__msg__Pose__fini(puppy_control_msgs__msg__Pose * msg)
{
  if (!msg) {
    return;
  }
  // roll
  // pitch
  // yaw
  // height
  // x_shift
  // stance_x
  // stance_y
  // run_time
}

bool
puppy_control_msgs__msg__Pose__are_equal(const puppy_control_msgs__msg__Pose * lhs, const puppy_control_msgs__msg__Pose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // x_shift
  if (lhs->x_shift != rhs->x_shift) {
    return false;
  }
  // stance_x
  if (lhs->stance_x != rhs->stance_x) {
    return false;
  }
  // stance_y
  if (lhs->stance_y != rhs->stance_y) {
    return false;
  }
  // run_time
  if (lhs->run_time != rhs->run_time) {
    return false;
  }
  return true;
}

bool
puppy_control_msgs__msg__Pose__copy(
  const puppy_control_msgs__msg__Pose * input,
  puppy_control_msgs__msg__Pose * output)
{
  if (!input || !output) {
    return false;
  }
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // height
  output->height = input->height;
  // x_shift
  output->x_shift = input->x_shift;
  // stance_x
  output->stance_x = input->stance_x;
  // stance_y
  output->stance_y = input->stance_y;
  // run_time
  output->run_time = input->run_time;
  return true;
}

puppy_control_msgs__msg__Pose *
puppy_control_msgs__msg__Pose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Pose * msg = (puppy_control_msgs__msg__Pose *)allocator.allocate(sizeof(puppy_control_msgs__msg__Pose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(puppy_control_msgs__msg__Pose));
  bool success = puppy_control_msgs__msg__Pose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
puppy_control_msgs__msg__Pose__destroy(puppy_control_msgs__msg__Pose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    puppy_control_msgs__msg__Pose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
puppy_control_msgs__msg__Pose__Sequence__init(puppy_control_msgs__msg__Pose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Pose * data = NULL;

  if (size) {
    data = (puppy_control_msgs__msg__Pose *)allocator.zero_allocate(size, sizeof(puppy_control_msgs__msg__Pose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = puppy_control_msgs__msg__Pose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        puppy_control_msgs__msg__Pose__fini(&data[i - 1]);
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
puppy_control_msgs__msg__Pose__Sequence__fini(puppy_control_msgs__msg__Pose__Sequence * array)
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
      puppy_control_msgs__msg__Pose__fini(&array->data[i]);
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

puppy_control_msgs__msg__Pose__Sequence *
puppy_control_msgs__msg__Pose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Pose__Sequence * array = (puppy_control_msgs__msg__Pose__Sequence *)allocator.allocate(sizeof(puppy_control_msgs__msg__Pose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = puppy_control_msgs__msg__Pose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
puppy_control_msgs__msg__Pose__Sequence__destroy(puppy_control_msgs__msg__Pose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    puppy_control_msgs__msg__Pose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
puppy_control_msgs__msg__Pose__Sequence__are_equal(const puppy_control_msgs__msg__Pose__Sequence * lhs, const puppy_control_msgs__msg__Pose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!puppy_control_msgs__msg__Pose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
puppy_control_msgs__msg__Pose__Sequence__copy(
  const puppy_control_msgs__msg__Pose__Sequence * input,
  puppy_control_msgs__msg__Pose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(puppy_control_msgs__msg__Pose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    puppy_control_msgs__msg__Pose * data =
      (puppy_control_msgs__msg__Pose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!puppy_control_msgs__msg__Pose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          puppy_control_msgs__msg__Pose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!puppy_control_msgs__msg__Pose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
