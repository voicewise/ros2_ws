// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from puppy_control_msgs:msg/SetServo.idl
// generated code does not contain a copyright notice
#include "puppy_control_msgs/msg/detail/set_servo__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
puppy_control_msgs__msg__SetServo__init(puppy_control_msgs__msg__SetServo * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // pulse
  // time
  return true;
}

void
puppy_control_msgs__msg__SetServo__fini(puppy_control_msgs__msg__SetServo * msg)
{
  if (!msg) {
    return;
  }
  // id
  // pulse
  // time
}

bool
puppy_control_msgs__msg__SetServo__are_equal(const puppy_control_msgs__msg__SetServo * lhs, const puppy_control_msgs__msg__SetServo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // pulse
  if (lhs->pulse != rhs->pulse) {
    return false;
  }
  // time
  if (lhs->time != rhs->time) {
    return false;
  }
  return true;
}

bool
puppy_control_msgs__msg__SetServo__copy(
  const puppy_control_msgs__msg__SetServo * input,
  puppy_control_msgs__msg__SetServo * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // pulse
  output->pulse = input->pulse;
  // time
  output->time = input->time;
  return true;
}

puppy_control_msgs__msg__SetServo *
puppy_control_msgs__msg__SetServo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__SetServo * msg = (puppy_control_msgs__msg__SetServo *)allocator.allocate(sizeof(puppy_control_msgs__msg__SetServo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(puppy_control_msgs__msg__SetServo));
  bool success = puppy_control_msgs__msg__SetServo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
puppy_control_msgs__msg__SetServo__destroy(puppy_control_msgs__msg__SetServo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    puppy_control_msgs__msg__SetServo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
puppy_control_msgs__msg__SetServo__Sequence__init(puppy_control_msgs__msg__SetServo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__SetServo * data = NULL;

  if (size) {
    data = (puppy_control_msgs__msg__SetServo *)allocator.zero_allocate(size, sizeof(puppy_control_msgs__msg__SetServo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = puppy_control_msgs__msg__SetServo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        puppy_control_msgs__msg__SetServo__fini(&data[i - 1]);
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
puppy_control_msgs__msg__SetServo__Sequence__fini(puppy_control_msgs__msg__SetServo__Sequence * array)
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
      puppy_control_msgs__msg__SetServo__fini(&array->data[i]);
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

puppy_control_msgs__msg__SetServo__Sequence *
puppy_control_msgs__msg__SetServo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  puppy_control_msgs__msg__SetServo__Sequence * array = (puppy_control_msgs__msg__SetServo__Sequence *)allocator.allocate(sizeof(puppy_control_msgs__msg__SetServo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = puppy_control_msgs__msg__SetServo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
puppy_control_msgs__msg__SetServo__Sequence__destroy(puppy_control_msgs__msg__SetServo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    puppy_control_msgs__msg__SetServo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
puppy_control_msgs__msg__SetServo__Sequence__are_equal(const puppy_control_msgs__msg__SetServo__Sequence * lhs, const puppy_control_msgs__msg__SetServo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!puppy_control_msgs__msg__SetServo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
puppy_control_msgs__msg__SetServo__Sequence__copy(
  const puppy_control_msgs__msg__SetServo__Sequence * input,
  puppy_control_msgs__msg__SetServo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(puppy_control_msgs__msg__SetServo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    puppy_control_msgs__msg__SetServo * data =
      (puppy_control_msgs__msg__SetServo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!puppy_control_msgs__msg__SetServo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          puppy_control_msgs__msg__SetServo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!puppy_control_msgs__msg__SetServo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
