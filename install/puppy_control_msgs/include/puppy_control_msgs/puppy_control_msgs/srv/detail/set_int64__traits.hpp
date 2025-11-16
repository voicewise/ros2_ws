// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from puppy_control_msgs:srv/SetInt64.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_INT64__TRAITS_HPP_
#define PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_INT64__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "puppy_control_msgs/srv/detail/set_int64__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace puppy_control_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetInt64_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetInt64_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetInt64_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace puppy_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use puppy_control_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const puppy_control_msgs::srv::SetInt64_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  puppy_control_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use puppy_control_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const puppy_control_msgs::srv::SetInt64_Request & msg)
{
  return puppy_control_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<puppy_control_msgs::srv::SetInt64_Request>()
{
  return "puppy_control_msgs::srv::SetInt64_Request";
}

template<>
inline const char * name<puppy_control_msgs::srv::SetInt64_Request>()
{
  return "puppy_control_msgs/srv/SetInt64_Request";
}

template<>
struct has_fixed_size<puppy_control_msgs::srv::SetInt64_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<puppy_control_msgs::srv::SetInt64_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<puppy_control_msgs::srv::SetInt64_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace puppy_control_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetInt64_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetInt64_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetInt64_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace puppy_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use puppy_control_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const puppy_control_msgs::srv::SetInt64_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  puppy_control_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use puppy_control_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const puppy_control_msgs::srv::SetInt64_Response & msg)
{
  return puppy_control_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<puppy_control_msgs::srv::SetInt64_Response>()
{
  return "puppy_control_msgs::srv::SetInt64_Response";
}

template<>
inline const char * name<puppy_control_msgs::srv::SetInt64_Response>()
{
  return "puppy_control_msgs/srv/SetInt64_Response";
}

template<>
struct has_fixed_size<puppy_control_msgs::srv::SetInt64_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<puppy_control_msgs::srv::SetInt64_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<puppy_control_msgs::srv::SetInt64_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<puppy_control_msgs::srv::SetInt64>()
{
  return "puppy_control_msgs::srv::SetInt64";
}

template<>
inline const char * name<puppy_control_msgs::srv::SetInt64>()
{
  return "puppy_control_msgs/srv/SetInt64";
}

template<>
struct has_fixed_size<puppy_control_msgs::srv::SetInt64>
  : std::integral_constant<
    bool,
    has_fixed_size<puppy_control_msgs::srv::SetInt64_Request>::value &&
    has_fixed_size<puppy_control_msgs::srv::SetInt64_Response>::value
  >
{
};

template<>
struct has_bounded_size<puppy_control_msgs::srv::SetInt64>
  : std::integral_constant<
    bool,
    has_bounded_size<puppy_control_msgs::srv::SetInt64_Request>::value &&
    has_bounded_size<puppy_control_msgs::srv::SetInt64_Response>::value
  >
{
};

template<>
struct is_service<puppy_control_msgs::srv::SetInt64>
  : std::true_type
{
};

template<>
struct is_service_request<puppy_control_msgs::srv::SetInt64_Request>
  : std::true_type
{
};

template<>
struct is_service_response<puppy_control_msgs::srv::SetInt64_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_INT64__TRAITS_HPP_
