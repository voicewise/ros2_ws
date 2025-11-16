// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__TRAITS_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "puppy_control_msgs/msg/detail/pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace puppy_control_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pose & msg,
  std::ostream & out)
{
  out << "{";
  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: x_shift
  {
    out << "x_shift: ";
    rosidl_generator_traits::value_to_yaml(msg.x_shift, out);
    out << ", ";
  }

  // member: stance_x
  {
    out << "stance_x: ";
    rosidl_generator_traits::value_to_yaml(msg.stance_x, out);
    out << ", ";
  }

  // member: stance_y
  {
    out << "stance_y: ";
    rosidl_generator_traits::value_to_yaml(msg.stance_y, out);
    out << ", ";
  }

  // member: run_time
  {
    out << "run_time: ";
    rosidl_generator_traits::value_to_yaml(msg.run_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: x_shift
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_shift: ";
    rosidl_generator_traits::value_to_yaml(msg.x_shift, out);
    out << "\n";
  }

  // member: stance_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stance_x: ";
    rosidl_generator_traits::value_to_yaml(msg.stance_x, out);
    out << "\n";
  }

  // member: stance_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stance_y: ";
    rosidl_generator_traits::value_to_yaml(msg.stance_y, out);
    out << "\n";
  }

  // member: run_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "run_time: ";
    rosidl_generator_traits::value_to_yaml(msg.run_time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pose & msg, bool use_flow_style = false)
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
  const puppy_control_msgs::msg::Pose & msg,
  std::ostream & out, size_t indentation = 0)
{
  puppy_control_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use puppy_control_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const puppy_control_msgs::msg::Pose & msg)
{
  return puppy_control_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<puppy_control_msgs::msg::Pose>()
{
  return "puppy_control_msgs::msg::Pose";
}

template<>
inline const char * name<puppy_control_msgs::msg::Pose>()
{
  return "puppy_control_msgs/msg/Pose";
}

template<>
struct has_fixed_size<puppy_control_msgs::msg::Pose>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<puppy_control_msgs::msg::Pose>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<puppy_control_msgs::msg::Pose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__TRAITS_HPP_
