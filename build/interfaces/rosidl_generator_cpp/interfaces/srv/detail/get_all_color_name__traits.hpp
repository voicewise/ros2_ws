// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:srv/GetAllColorName.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__TRAITS_HPP_
#define INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/srv/detail/get_all_color_name__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAllColorName_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAllColorName_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAllColorName_Request & msg, bool use_flow_style = false)
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

}  // namespace interfaces

namespace rosidl_generator_traits
{

[[deprecated("use interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interfaces::srv::GetAllColorName_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::GetAllColorName_Request & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::GetAllColorName_Request>()
{
  return "interfaces::srv::GetAllColorName_Request";
}

template<>
inline const char * name<interfaces::srv::GetAllColorName_Request>()
{
  return "interfaces/srv/GetAllColorName_Request";
}

template<>
struct has_fixed_size<interfaces::srv::GetAllColorName_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::srv::GetAllColorName_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::srv::GetAllColorName_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAllColorName_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: color_names
  {
    if (msg.color_names.size() == 0) {
      out << "color_names: []";
    } else {
      out << "color_names: [";
      size_t pending_items = msg.color_names.size();
      for (auto item : msg.color_names) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAllColorName_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: color_names
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.color_names.size() == 0) {
      out << "color_names: []\n";
    } else {
      out << "color_names:\n";
      for (auto item : msg.color_names) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAllColorName_Response & msg, bool use_flow_style = false)
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

}  // namespace interfaces

namespace rosidl_generator_traits
{

[[deprecated("use interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interfaces::srv::GetAllColorName_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::GetAllColorName_Response & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::GetAllColorName_Response>()
{
  return "interfaces::srv::GetAllColorName_Response";
}

template<>
inline const char * name<interfaces::srv::GetAllColorName_Response>()
{
  return "interfaces/srv/GetAllColorName_Response";
}

template<>
struct has_fixed_size<interfaces::srv::GetAllColorName_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interfaces::srv::GetAllColorName_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interfaces::srv::GetAllColorName_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<interfaces::srv::GetAllColorName>()
{
  return "interfaces::srv::GetAllColorName";
}

template<>
inline const char * name<interfaces::srv::GetAllColorName>()
{
  return "interfaces/srv/GetAllColorName";
}

template<>
struct has_fixed_size<interfaces::srv::GetAllColorName>
  : std::integral_constant<
    bool,
    has_fixed_size<interfaces::srv::GetAllColorName_Request>::value &&
    has_fixed_size<interfaces::srv::GetAllColorName_Response>::value
  >
{
};

template<>
struct has_bounded_size<interfaces::srv::GetAllColorName>
  : std::integral_constant<
    bool,
    has_bounded_size<interfaces::srv::GetAllColorName_Request>::value &&
    has_bounded_size<interfaces::srv::GetAllColorName_Response>::value
  >
{
};

template<>
struct is_service<interfaces::srv::GetAllColorName>
  : std::true_type
{
};

template<>
struct is_service_request<interfaces::srv::GetAllColorName_Request>
  : std::true_type
{
};

template<>
struct is_service_response<interfaces::srv::GetAllColorName_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__TRAITS_HPP_
