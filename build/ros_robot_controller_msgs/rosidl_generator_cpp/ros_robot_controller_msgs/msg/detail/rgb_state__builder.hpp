// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ros_robot_controller_msgs:msg/RGBState.idl
// generated code does not contain a copyright notice

#ifndef ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RGB_STATE__BUILDER_HPP_
#define ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RGB_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ros_robot_controller_msgs/msg/detail/rgb_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ros_robot_controller_msgs
{

namespace msg
{

namespace builder
{

class Init_RGBState_b
{
public:
  explicit Init_RGBState_b(::ros_robot_controller_msgs::msg::RGBState & msg)
  : msg_(msg)
  {}
  ::ros_robot_controller_msgs::msg::RGBState b(::ros_robot_controller_msgs::msg::RGBState::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros_robot_controller_msgs::msg::RGBState msg_;
};

class Init_RGBState_g
{
public:
  explicit Init_RGBState_g(::ros_robot_controller_msgs::msg::RGBState & msg)
  : msg_(msg)
  {}
  Init_RGBState_b g(::ros_robot_controller_msgs::msg::RGBState::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_RGBState_b(msg_);
  }

private:
  ::ros_robot_controller_msgs::msg::RGBState msg_;
};

class Init_RGBState_r
{
public:
  explicit Init_RGBState_r(::ros_robot_controller_msgs::msg::RGBState & msg)
  : msg_(msg)
  {}
  Init_RGBState_g r(::ros_robot_controller_msgs::msg::RGBState::_r_type arg)
  {
    msg_.r = std::move(arg);
    return Init_RGBState_g(msg_);
  }

private:
  ::ros_robot_controller_msgs::msg::RGBState msg_;
};

class Init_RGBState_id
{
public:
  Init_RGBState_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RGBState_r id(::ros_robot_controller_msgs::msg::RGBState::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_RGBState_r(msg_);
  }

private:
  ::ros_robot_controller_msgs::msg::RGBState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros_robot_controller_msgs::msg::RGBState>()
{
  return ros_robot_controller_msgs::msg::builder::Init_RGBState_id();
}

}  // namespace ros_robot_controller_msgs

#endif  // ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RGB_STATE__BUILDER_HPP_
