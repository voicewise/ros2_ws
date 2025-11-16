// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from puppy_control_msgs:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__TRAITS_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "puppy_control_msgs/msg/detail/velocity__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace puppy_control_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Velocity & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: yaw_rate
  {
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Velocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: yaw_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Velocity & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace puppy_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use puppy_control_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const puppy_control_msgs::msg::Velocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  puppy_control_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use puppy_control_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const puppy_control_msgs::msg::Velocity & msg)
{
  return puppy_control_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<puppy_control_msgs::msg::Velocity>()
{
  return "puppy_control_msgs::msg::Velocity";
}

template<>
inline const char * name<puppy_control_msgs::msg::Velocity>()
{
  return "puppy_control_msgs/msg/Velocity";
}

template<>
struct has_fixed_size<puppy_control_msgs::msg::Velocity>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<puppy_control_msgs::msg::Velocity>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<puppy_control_msgs::msg::Velocity>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__TRAITS_HPP_
