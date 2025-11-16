// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from puppy_control_msgs:msg/Gait.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_H_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Gait in the package puppy_control_msgs.
typedef struct puppy_control_msgs__msg__Gait
{
  float overlap_time;
  float swing_time;
  float clearance_time;
  float z_clearance;
} puppy_control_msgs__msg__Gait;

// Struct for a sequence of puppy_control_msgs__msg__Gait.
typedef struct puppy_control_msgs__msg__Gait__Sequence
{
  puppy_control_msgs__msg__Gait * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puppy_control_msgs__msg__Gait__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_H_
