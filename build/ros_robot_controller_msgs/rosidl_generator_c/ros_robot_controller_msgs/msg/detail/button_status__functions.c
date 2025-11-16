// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ros_robot_controller_msgs:msg/ButtonStatus.idl
// generated code does not contain a copyright notice
#include "ros_robot_controller_msgs/msg/detail/button_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
ros_robot_controller_msgs__msg__ButtonStatus__init(ros_robot_controller_msgs__msg__ButtonStatus * msg)
{
  if (!msg) {
    return false;
  }
  // key1
  // key2
  return true;
}

void
ros_robot_controller_msgs__msg__ButtonStatus__fini(ros_robot_controller_msgs__msg__ButtonStatus * msg)
{
  if (!msg) {
    return;
  }
  // key1
  // key2
}

bool
ros_robot_controller_msgs__msg__ButtonStatus__are_equal(const ros_robot_controller_msgs__msg__ButtonStatus * lhs, const ros_robot_controller_msgs__msg__ButtonStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // key1
  if (lhs->key1 != rhs->key1) {
    return false;
  }
  // key2
  if (lhs->key2 != rhs->key2) {
    return false;
  }
  return true;
}

bool
ros_robot_controller_msgs__msg__ButtonStatus__copy(
  const ros_robot_controller_msgs__msg__ButtonStatus * input,
  ros_robot_controller_msgs__msg__ButtonStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // key1
  output->key1 = input->key1;
  // key2
  output->key2 = input->key2;
  return true;
}

ros_robot_controller_msgs__msg__ButtonStatus *
ros_robot_controller_msgs__msg__ButtonStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros_robot_controller_msgs__msg__ButtonStatus * msg = (ros_robot_controller_msgs__msg__ButtonStatus *)allocator.allocate(sizeof(ros_robot_controller_msgs__msg__ButtonStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ros_robot_controller_msgs__msg__ButtonStatus));
  bool success = ros_robot_controller_msgs__msg__ButtonStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ros_robot_controller_msgs__msg__ButtonStatus__destroy(ros_robot_controller_msgs__msg__ButtonStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ros_robot_controller_msgs__msg__ButtonStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__init(ros_robot_controller_msgs__msg__ButtonStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros_robot_controller_msgs__msg__ButtonStatus * data = NULL;

  if (size) {
    data = (ros_robot_controller_msgs__msg__ButtonStatus *)allocator.zero_allocate(size, sizeof(ros_robot_controller_msgs__msg__ButtonStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ros_robot_controller_msgs__msg__ButtonStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ros_robot_controller_msgs__msg__ButtonStatus__fini(&data[i - 1]);
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
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__fini(ros_robot_controller_msgs__msg__ButtonStatus__Sequence * array)
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
      ros_robot_controller_msgs__msg__ButtonStatus__fini(&array->data[i]);
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

ros_robot_controller_msgs__msg__ButtonStatus__Sequence *
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros_robot_controller_msgs__msg__ButtonStatus__Sequence * array = (ros_robot_controller_msgs__msg__ButtonStatus__Sequence *)allocator.allocate(sizeof(ros_robot_controller_msgs__msg__ButtonStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ros_robot_controller_msgs__msg__ButtonStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__destroy(ros_robot_controller_msgs__msg__ButtonStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ros_robot_controller_msgs__msg__ButtonStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__are_equal(const ros_robot_controller_msgs__msg__ButtonStatus__Sequence * lhs, const ros_robot_controller_msgs__msg__ButtonStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ros_robot_controller_msgs__msg__ButtonStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ros_robot_controller_msgs__msg__ButtonStatus__Sequence__copy(
  const ros_robot_controller_msgs__msg__ButtonStatus__Sequence * input,
  ros_robot_controller_msgs__msg__ButtonStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ros_robot_controller_msgs__msg__ButtonStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ros_robot_controller_msgs__msg__ButtonStatus * data =
      (ros_robot_controller_msgs__msg__ButtonStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ros_robot_controller_msgs__msg__ButtonStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ros_robot_controller_msgs__msg__ButtonStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ros_robot_controller_msgs__msg__ButtonStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
