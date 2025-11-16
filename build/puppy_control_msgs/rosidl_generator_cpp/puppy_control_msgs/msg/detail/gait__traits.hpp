// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from puppy_control_msgs:msg/Gait.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__TRAITS_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "puppy_control_msgs/msg/detail/gait__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace puppy_control_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Gait & msg,
  std::ostream & out)
{
  out << "{";
  // member: overlap_time
  {
    out << "overlap_time: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_time, out);
    out << ", ";
  }

  // member: swing_time
  {
    out << "swing_time: ";
    rosidl_generator_traits::value_to_yaml(msg.swing_time, out);
    out << ", ";
  }

  // member: clearance_time
  {
    out << "clearance_time: ";
    rosidl_generator_traits::value_to_yaml(msg.clearance_time, out);
    out << ", ";
  }

  // member: z_clearance
  {
    out << "z_clearance: ";
    rosidl_generator_traits::value_to_yaml(msg.z_clearance, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Gait & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: overlap_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overlap_time: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_time, out);
    out << "\n";
  }

  // member: swing_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "swing_time: ";
    rosidl_generator_traits::value_to_yaml(msg.swing_time, out);
    out << "\n";
  }

  // member: clearance_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "clearance_time: ";
    rosidl_generator_traits::value_to_yaml(msg.clearance_time, out);
    out << "\n";
  }

  // member: z_clearance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z_clearance: ";
    rosidl_generator_traits::value_to_yaml(msg.z_clearance, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Gait & msg, bool use_flow_style = false)
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
  const puppy_control_msgs::msg::Gait & msg,
  std::ostream & out, size_t indentation = 0)
{
  puppy_control_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use puppy_control_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const puppy_control_msgs::msg::Gait & msg)
{
  return puppy_control_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<puppy_control_msgs::msg::Gait>()
{
  return "puppy_control_msgs::msg::Gait";
}

template<>
inline const char * name<puppy_control_msgs::msg::Gait>()
{
  return "puppy_control_msgs/msg/Gait";
}

template<>
struct has_fixed_size<puppy_control_msgs::msg::Gait>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<puppy_control_msgs::msg::Gait>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<puppy_control_msgs::msg::Gait>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__TRAITS_HPP_
