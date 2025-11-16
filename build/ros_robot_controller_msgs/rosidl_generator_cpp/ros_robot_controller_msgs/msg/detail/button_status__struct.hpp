// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros_robot_controller_msgs:msg/ButtonStatus.idl
// generated code does not contain a copyright notice

#ifndef ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__BUTTON_STATUS__STRUCT_HPP_
#define ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__BUTTON_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ros_robot_controller_msgs__msg__ButtonStatus __attribute__((deprecated))
#else
# define DEPRECATED__ros_robot_controller_msgs__msg__ButtonStatus __declspec(deprecated)
#endif

namespace ros_robot_controller_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ButtonStatus_
{
  using Type = ButtonStatus_<ContainerAllocator>;

  explicit ButtonStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->key1 = 0l;
      this->key2 = 0l;
    }
  }

  explicit ButtonStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->key1 = 0l;
      this->key2 = 0l;
    }
  }

  // field types and members
  using _key1_type =
    int32_t;
  _key1_type key1;
  using _key2_type =
    int32_t;
  _key2_type key2;

  // setters for named parameter idiom
  Type & set__key1(
    const int32_t & _arg)
  {
    this->key1 = _arg;
    return *this;
  }
  Type & set__key2(
    const int32_t & _arg)
  {
    this->key2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros_robot_controller_msgs__msg__ButtonStatus
    std::shared_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros_robot_controller_msgs__msg__ButtonStatus
    std::shared_ptr<ros_robot_controller_msgs::msg::ButtonStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ButtonStatus_ & other) const
  {
    if (this->key1 != other.key1) {
      return false;
    }
    if (this->key2 != other.key2) {
      return false;
    }
    return true;
  }
  bool operator!=(const ButtonStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ButtonStatus_

// alias to use template instance with default allocator
using ButtonStatus =
  ros_robot_controller_msgs::msg::ButtonStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ros_robot_controller_msgs

#endif  // ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__BUTTON_STATUS__STRUCT_HPP_
