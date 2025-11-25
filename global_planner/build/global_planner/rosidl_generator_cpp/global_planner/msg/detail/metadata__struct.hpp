// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from global_planner:msg/Metadata.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__global_planner__msg__Metadata __attribute__((deprecated))
#else
# define DEPRECATED__global_planner__msg__Metadata __declspec(deprecated)
#endif

namespace global_planner
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Metadata_
{
  using Type = Metadata_<ContainerAllocator>;

  explicit Metadata_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->average_speed = 0.0f;
      this->total_time = 0.0f;
      this->lap_time = 0.0f;
    }
  }

  explicit Metadata_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->average_speed = 0.0f;
      this->total_time = 0.0f;
      this->lap_time = 0.0f;
    }
  }

  // field types and members
  using _average_speed_type =
    float;
  _average_speed_type average_speed;
  using _total_time_type =
    float;
  _total_time_type total_time;
  using _lap_time_type =
    float;
  _lap_time_type lap_time;

  // setters for named parameter idiom
  Type & set__average_speed(
    const float & _arg)
  {
    this->average_speed = _arg;
    return *this;
  }
  Type & set__total_time(
    const float & _arg)
  {
    this->total_time = _arg;
    return *this;
  }
  Type & set__lap_time(
    const float & _arg)
  {
    this->lap_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    global_planner::msg::Metadata_<ContainerAllocator> *;
  using ConstRawPtr =
    const global_planner::msg::Metadata_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<global_planner::msg::Metadata_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<global_planner::msg::Metadata_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::Metadata_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::Metadata_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::Metadata_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::Metadata_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<global_planner::msg::Metadata_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<global_planner::msg::Metadata_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__global_planner__msg__Metadata
    std::shared_ptr<global_planner::msg::Metadata_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__global_planner__msg__Metadata
    std::shared_ptr<global_planner::msg::Metadata_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Metadata_ & other) const
  {
    if (this->average_speed != other.average_speed) {
      return false;
    }
    if (this->total_time != other.total_time) {
      return false;
    }
    if (this->lap_time != other.lap_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Metadata_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Metadata_

// alias to use template instance with default allocator
using Metadata =
  global_planner::msg::Metadata_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_HPP_
