// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:srv/ChangeRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__CHANGE_RANGE__TRAITS_HPP_
#define INTERFACES__SRV__DETAIL__CHANGE_RANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/srv/detail/change_range__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeRange_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: min
  {
    if (msg.min.size() == 0) {
      out << "min: []";
    } else {
      out << "min: [";
      size_t pending_items = msg.min.size();
      for (auto item : msg.min) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: max
  {
    if (msg.max.size() == 0) {
      out << "max: []";
    } else {
      out << "max: [";
      size_t pending_items = msg.max.size();
      for (auto item : msg.max) {
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
  const ChangeRange_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.min.size() == 0) {
      out << "min: []\n";
    } else {
      out << "min:\n";
      for (auto item : msg.min) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.max.size() == 0) {
      out << "max: []\n";
    } else {
      out << "max:\n";
      for (auto item : msg.max) {
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

inline std::string to_yaml(const ChangeRange_Request & msg, bool use_flow_style = false)
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
  const interfaces::srv::ChangeRange_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::ChangeRange_Request & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::ChangeRange_Request>()
{
  return "interfaces::srv::ChangeRange_Request";
}

template<>
inline const char * name<interfaces::srv::ChangeRange_Request>()
{
  return "interfaces/srv/ChangeRange_Request";
}

template<>
struct has_fixed_size<interfaces::srv::ChangeRange_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interfaces::srv::ChangeRange_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interfaces::srv::ChangeRange_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeRange_Response & msg,
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
  const ChangeRange_Response & msg,
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

inline std::string to_yaml(const ChangeRange_Response & msg, bool use_flow_style = false)
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
  const interfaces::srv::ChangeRange_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::ChangeRange_Response & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::ChangeRange_Response>()
{
  return "interfaces::srv::ChangeRange_Response";
}

template<>
inline const char * name<interfaces::srv::ChangeRange_Response>()
{
  return "interfaces/srv/ChangeRange_Response";
}

template<>
struct has_fixed_size<interfaces::srv::ChangeRange_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interfaces::srv::ChangeRange_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interfaces::srv::ChangeRange_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<interfaces::srv::ChangeRange>()
{
  return "interfaces::srv::ChangeRange";
}

template<>
inline const char * name<interfaces::srv::ChangeRange>()
{
  return "interfaces/srv/ChangeRange";
}

template<>
struct has_fixed_size<interfaces::srv::ChangeRange>
  : std::integral_constant<
    bool,
    has_fixed_size<interfaces::srv::ChangeRange_Request>::value &&
    has_fixed_size<interfaces::srv::ChangeRange_Response>::value
  >
{
};

template<>
struct has_bounded_size<interfaces::srv::ChangeRange>
  : std::integral_constant<
    bool,
    has_bounded_size<interfaces::srv::ChangeRange_Request>::value &&
    has_bounded_size<interfaces::srv::ChangeRange_Response>::value
  >
{
};

template<>
struct is_service<interfaces::srv::ChangeRange>
  : std::true_type
{
};

template<>
struct is_service_request<interfaces::srv::ChangeRange_Request>
  : std::true_type
{
};

template<>
struct is_service_response<interfaces::srv::ChangeRange_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__SRV__DETAIL__CHANGE_RANGE__TRAITS_HPP_
