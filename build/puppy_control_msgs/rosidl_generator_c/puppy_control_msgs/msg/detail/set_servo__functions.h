// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from puppy_control_msgs:msg/SetServo.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__FUNCTIONS_H_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "puppy_control_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "puppy_control_msgs/msg/detail/set_servo__struct.h"

/// Initialize msg/SetServo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * puppy_control_msgs__msg__SetServo
 * )) before or use
 * puppy_control_msgs__msg__SetServo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__init(puppy_control_msgs__msg__SetServo * msg);

/// Finalize msg/SetServo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
void
puppy_control_msgs__msg__SetServo__fini(puppy_control_msgs__msg__SetServo * msg);

/// Create msg/SetServo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * puppy_control_msgs__msg__SetServo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
puppy_control_msgs__msg__SetServo *
puppy_control_msgs__msg__SetServo__create();

/// Destroy msg/SetServo message.
/**
 * It calls
 * puppy_control_msgs__msg__SetServo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
void
puppy_control_msgs__msg__SetServo__destroy(puppy_control_msgs__msg__SetServo * msg);

/// Check for msg/SetServo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__are_equal(const puppy_control_msgs__msg__SetServo * lhs, const puppy_control_msgs__msg__SetServo * rhs);

/// Copy a msg/SetServo message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__copy(
  const puppy_control_msgs__msg__SetServo * input,
  puppy_control_msgs__msg__SetServo * output);

/// Initialize array of msg/SetServo messages.
/**
 * It allocates the memory for the number of elements and calls
 * puppy_control_msgs__msg__SetServo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__Sequence__init(puppy_control_msgs__msg__SetServo__Sequence * array, size_t size);

/// Finalize array of msg/SetServo messages.
/**
 * It calls
 * puppy_control_msgs__msg__SetServo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
void
puppy_control_msgs__msg__SetServo__Sequence__fini(puppy_control_msgs__msg__SetServo__Sequence * array);

/// Create array of msg/SetServo messages.
/**
 * It allocates the memory for the array and calls
 * puppy_control_msgs__msg__SetServo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
puppy_control_msgs__msg__SetServo__Sequence *
puppy_control_msgs__msg__SetServo__Sequence__create(size_t size);

/// Destroy array of msg/SetServo messages.
/**
 * It calls
 * puppy_control_msgs__msg__SetServo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
void
puppy_control_msgs__msg__SetServo__Sequence__destroy(puppy_control_msgs__msg__SetServo__Sequence * array);

/// Check for msg/SetServo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__Sequence__are_equal(const puppy_control_msgs__msg__SetServo__Sequence * lhs, const puppy_control_msgs__msg__SetServo__Sequence * rhs);

/// Copy an array of msg/SetServo messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_puppy_control_msgs
bool
puppy_control_msgs__msg__SetServo__Sequence__copy(
  const puppy_control_msgs__msg__SetServo__Sequence * input,
  puppy_control_msgs__msg__SetServo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__FUNCTIONS_H_
