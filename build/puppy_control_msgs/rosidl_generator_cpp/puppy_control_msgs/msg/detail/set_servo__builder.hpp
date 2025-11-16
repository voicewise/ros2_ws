// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puppy_control_msgs:msg/SetServo.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__BUILDER_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puppy_control_msgs/msg/detail/set_servo__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puppy_control_msgs
{

namespace msg
{

namespace builder
{

class Init_SetServo_time
{
public:
  explicit Init_SetServo_time(::puppy_control_msgs::msg::SetServo & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::msg::SetServo time(::puppy_control_msgs::msg::SetServo::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::msg::SetServo msg_;
};

class Init_SetServo_pulse
{
public:
  explicit Init_SetServo_pulse(::puppy_control_msgs::msg::SetServo & msg)
  : msg_(msg)
  {}
  Init_SetServo_time pulse(::puppy_control_msgs::msg::SetServo::_pulse_type arg)
  {
    msg_.pulse = std::move(arg);
    return Init_SetServo_time(msg_);
  }

private:
  ::puppy_control_msgs::msg::SetServo msg_;
};

class Init_SetServo_id
{
public:
  Init_SetServo_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetServo_pulse id(::puppy_control_msgs::msg::SetServo::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetServo_pulse(msg_);
  }

private:
  ::puppy_control_msgs::msg::SetServo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::msg::SetServo>()
{
  return puppy_control_msgs::msg::builder::Init_SetServo_id();
}

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__BUILDER_HPP_
