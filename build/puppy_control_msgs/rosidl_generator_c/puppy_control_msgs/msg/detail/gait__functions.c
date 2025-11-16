// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from puppy_control_msgs:msg/Gait.idl
// generated code does not contain a copyright notice
#include "puppy_control_msgs/msg/detail/gait__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
puppy_control_msgs__msg__Gait__init(puppy_control_msgs__msg__Gait * msg)
{
  if (!msg) {
    return false;
  }
  // overlap_time
  // swing_time
  // clearance_time
  // z_clearance
  return true;
}

void
puppy_control_msgs__msg__Gait__fini(puppy_control_msgs__msg__Gait * msg)
{
  if (!msg) {
    return;
  }
  // overlap_time
  // swing_time
  // clearance_time
  // z_clearance
}

bool
puppy_control_msgs__msg__Gait__are_equal(const puppy_control_msgs__msg__Gait * lhs, const puppy_control_msgs__msg__Gait * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // overlap_time
  if (lhs->overlap_time != rhs->overlap_time) {
    return false;
  }
  // swing_time
  if (lhs->swing_time != rhs->swing_time) {
    return false;
  }
  // clearance_time
  if (lhs->clearance_time != rhs->clearance_time) {
    return false;
  }
  // z_clearance
  if (lhs->z_clearance != rhs->z_clearance) {
    return false;
  }
  return true;
}

bool
puppy_control_msgs__msg__Gait__copy(
  const puppy_control_msgs__msg__Gait * input,
  puppy_control_msgs__msg__Gait * output)
{
  if (!input || !output) {
    return false;
  }
  // overlap_time
  output->overlap_time = input->overlap_time;
  // swing_time
  output->swing_time = input->swing_time;
  // clearance_time
  output->clearance_time = input->clearance_time;
  // z_clearance
  output->z_clearance = input->z_clearance;
  return true;
}

puppy_control_msgs__msg__Gait *
puppy_control_msgs__msg__Gait__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Gait * msg = (puppy_control_msgs__msg__Gait *)allocator.allocate(sizeof(puppy_control_msgs__msg__Gait), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(puppy_control_msgs__msg__Gait));
  bool success = puppy_control_msgs__msg__Gait__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
puppy_control_msgs__msg__Gait__destroy(puppy_control_msgs__msg__Gait * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    puppy_control_msgs__msg__Gait__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
puppy_control_msgs__msg__Gait__Sequence__init(puppy_control_msgs__msg__Gait__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Gait * data = NULL;

  if (size) {
    data = (puppy_control_msgs__msg__Gait *)allocator.zero_allocate(size, sizeof(puppy_control_msgs__msg__Gait), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = puppy_control_msgs__msg__Gait__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        puppy_control_msgs__msg__Gait__fini(&data[i - 1]);
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
puppy_control_msgs__msg__Gait__Sequence__fini(puppy_control_msgs__msg__Gait__Sequence * array)
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
      puppy_control_msgs__msg__Gait__fini(&array->data[i]);
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

puppy_control_msgs__msg__Gait__Sequence *
puppy_control_msgs__msg__Gait__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__Gait__Sequence * array = (puppy_control_msgs__msg__Gait__Sequence *)allocator.allocate(sizeof(puppy_control_msgs__msg__Gait__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = puppy_control_msgs__msg__Gait__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
puppy_control_msgs__msg__Gait__Sequence__destroy(puppy_control_msgs__msg__Gait__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    puppy_control_msgs__msg__Gait__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
puppy_control_msgs__msg__Gait__Sequence__are_equal(const puppy_control_msgs__msg__Gait__Sequence * lhs, const puppy_control_msgs__msg__Gait__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!puppy_control_msgs__msg__Gait__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
puppy_control_msgs__msg__Gait__Sequence__copy(
  const puppy_control_msgs__msg__Gait__Sequence * input,
  puppy_control_msgs__msg__Gait__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(puppy_control_msgs__msg__Gait);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    puppy_control_msgs__msg__Gait * data =
      (puppy_control_msgs__msg__Gait *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!puppy_control_msgs__msg__Gait__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          puppy_control_msgs__msg__Gait__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!puppy_control_msgs__msg__Gait__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
