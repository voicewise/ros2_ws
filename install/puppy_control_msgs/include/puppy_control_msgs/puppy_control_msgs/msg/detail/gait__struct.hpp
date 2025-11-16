// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from puppy_control_msgs:msg/Gait.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__msg__Gait __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__msg__Gait __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Gait_
{
  using Type = Gait_<ContainerAllocator>;

  explicit Gait_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->overlap_time = 0.0f;
      this->swing_time = 0.0f;
      this->clearance_time = 0.0f;
      this->z_clearance = 0.0f;
    }
  }

  explicit Gait_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->overlap_time = 0.0f;
      this->swing_time = 0.0f;
      this->clearance_time = 0.0f;
      this->z_clearance = 0.0f;
    }
  }

  // field types and members
  using _overlap_time_type =
    float;
  _overlap_time_type overlap_time;
  using _swing_time_type =
    float;
  _swing_time_type swing_time;
  using _clearance_time_type =
    float;
  _clearance_time_type clearance_time;
  using _z_clearance_type =
    float;
  _z_clearance_type z_clearance;

  // setters for named parameter idiom
  Type & set__overlap_time(
    const float & _arg)
  {
    this->overlap_time = _arg;
    return *this;
  }
  Type & set__swing_time(
    const float & _arg)
  {
    this->swing_time = _arg;
    return *this;
  }
  Type & set__clearance_time(
    const float & _arg)
  {
    this->clearance_time = _arg;
    return *this;
  }
  Type & set__z_clearance(
    const float & _arg)
  {
    this->z_clearance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::msg::Gait_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::msg::Gait_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::Gait_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::Gait_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__msg__Gait
    std::shared_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__msg__Gait
    std::shared_ptr<puppy_control_msgs::msg::Gait_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Gait_ & other) const
  {
    if (this->overlap_time != other.overlap_time) {
      return false;
    }
    if (this->swing_time != other.swing_time) {
      return false;
    }
    if (this->clearance_time != other.clearance_time) {
      return false;
    }
    if (this->z_clearance != other.z_clearance) {
      return false;
    }
    return true;
  }
  bool operator!=(const Gait_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Gait_

// alias to use template instance with default allocator
using Gait =
  puppy_control_msgs::msg::Gait_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__STRUCT_HPP_
