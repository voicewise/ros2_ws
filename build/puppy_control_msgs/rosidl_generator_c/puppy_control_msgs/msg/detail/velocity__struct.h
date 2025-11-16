// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from puppy_control_msgs:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__STRUCT_H_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Velocity in the package puppy_control_msgs.
typedef struct puppy_control_msgs__msg__Velocity
{
  float x;
  float y;
  float yaw_rate;
} puppy_control_msgs__msg__Velocity;

// Struct for a sequence of puppy_control_msgs__msg__Velocity.
typedef struct puppy_control_msgs__msg__Velocity__Sequence
{
  puppy_control_msgs__msg__Velocity * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puppy_control_msgs__msg__Velocity__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__STRUCT_H_
