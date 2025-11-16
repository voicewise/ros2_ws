// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from puppy_control_msgs:msg/SetServo.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__STRUCT_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__msg__SetServo __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__msg__SetServo __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SetServo_
{
  using Type = SetServo_<ContainerAllocator>;

  explicit SetServo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->pulse = 0l;
      this->time = 0l;
    }
  }

  explicit SetServo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->pulse = 0l;
      this->time = 0l;
    }
  }

  // field types and members
  using _id_type =
    int32_t;
  _id_type id;
  using _pulse_type =
    int32_t;
  _pulse_type pulse;
  using _time_type =
    int32_t;
  _time_type time;

  // setters for named parameter idiom
  Type & set__id(
    const int32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__pulse(
    const int32_t & _arg)
  {
    this->pulse = _arg;
    return *this;
  }
  Type & set__time(
    const int32_t & _arg)
  {
    this->time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::msg::SetServo_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::msg::SetServo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::SetServo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::SetServo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__msg__SetServo
    std::shared_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__msg__SetServo
    std::shared_ptr<puppy_control_msgs::msg::SetServo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetServo_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->pulse != other.pulse) {
      return false;
    }
    if (this->time != other.time) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetServo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetServo_

// alias to use template instance with default allocator
using SetServo =
  puppy_control_msgs::msg::SetServo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__SET_SERVO__STRUCT_HPP_
