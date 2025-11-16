// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:srv/GetRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__GET_RANGE__STRUCT_H_
#define INTERFACES__SRV__DETAIL__GET_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'color_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetRange in the package interfaces.
typedef struct interfaces__srv__GetRange_Request
{
  rosidl_runtime_c__String color_name;
} interfaces__srv__GetRange_Request;

// Struct for a sequence of interfaces__srv__GetRange_Request.
typedef struct interfaces__srv__GetRange_Request__Sequence
{
  interfaces__srv__GetRange_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__srv__GetRange_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'min'
// Member 'max'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/GetRange in the package interfaces.
typedef struct interfaces__srv__GetRange_Response
{
  bool success;
  rosidl_runtime_c__int16__Sequence min;
  rosidl_runtime_c__int16__Sequence max;
} interfaces__srv__GetRange_Response;

// Struct for a sequence of interfaces__srv__GetRange_Response.
typedef struct interfaces__srv__GetRange_Response__Sequence
{
  interfaces__srv__GetRange_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__srv__GetRange_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__SRV__DETAIL__GET_RANGE__STRUCT_H_
