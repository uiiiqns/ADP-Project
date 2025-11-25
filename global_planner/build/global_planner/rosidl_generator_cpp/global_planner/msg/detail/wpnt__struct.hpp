// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__global_planner__msg__Wpnt __attribute__((deprecated))
#else
# define DEPRECATED__global_planner__msg__Wpnt __declspec(deprecated)
#endif

namespace global_planner
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Wpnt_
{
  using Type = Wpnt_<ContainerAllocator>;

  explicit Wpnt_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->yaw = 0.0f;
      this->curvature = 0.0f;
      this->velocity = 0.0f;
    }
  }

  explicit Wpnt_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->yaw = 0.0f;
      this->curvature = 0.0f;
      this->velocity = 0.0f;
    }
  }

  // field types and members
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _curvature_type =
    float;
  _curvature_type curvature;
  using _velocity_type =
    float;
  _velocity_type velocity;

  // setters for named parameter idiom
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__curvature(
    const float & _arg)
  {
    this->curvature = _arg;
    return *this;
  }
  Type & set__velocity(
    const float & _arg)
  {
    this->velocity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    global_planner::msg::Wpnt_<ContainerAllocator> *;
  using ConstRawPtr =
    const global_planner::msg::Wpnt_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<global_planner::msg::Wpnt_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<global_planner::msg::Wpnt_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::Wpnt_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::Wpnt_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::Wpnt_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::Wpnt_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<global_planner::msg::Wpnt_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<global_planner::msg::Wpnt_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__global_planner__msg__Wpnt
    std::shared_ptr<global_planner::msg::Wpnt_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__global_planner__msg__Wpnt
    std::shared_ptr<global_planner::msg::Wpnt_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Wpnt_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->curvature != other.curvature) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    return true;
  }
  bool operator!=(const Wpnt_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Wpnt_

// alias to use template instance with default allocator
using Wpnt =
  global_planner::msg::Wpnt_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_HPP_
