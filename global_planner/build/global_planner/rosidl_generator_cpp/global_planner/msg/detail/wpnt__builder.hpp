// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT__BUILDER_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "global_planner/msg/detail/wpnt__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace global_planner
{

namespace msg
{

namespace builder
{

class Init_Wpnt_velocity
{
public:
  explicit Init_Wpnt_velocity(::global_planner::msg::Wpnt & msg)
  : msg_(msg)
  {}
  ::global_planner::msg::Wpnt velocity(::global_planner::msg::Wpnt::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::global_planner::msg::Wpnt msg_;
};

class Init_Wpnt_curvature
{
public:
  explicit Init_Wpnt_curvature(::global_planner::msg::Wpnt & msg)
  : msg_(msg)
  {}
  Init_Wpnt_velocity curvature(::global_planner::msg::Wpnt::_curvature_type arg)
  {
    msg_.curvature = std::move(arg);
    return Init_Wpnt_velocity(msg_);
  }

private:
  ::global_planner::msg::Wpnt msg_;
};

class Init_Wpnt_yaw
{
public:
  explicit Init_Wpnt_yaw(::global_planner::msg::Wpnt & msg)
  : msg_(msg)
  {}
  Init_Wpnt_curvature yaw(::global_planner::msg::Wpnt::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_Wpnt_curvature(msg_);
  }

private:
  ::global_planner::msg::Wpnt msg_;
};

class Init_Wpnt_y
{
public:
  explicit Init_Wpnt_y(::global_planner::msg::Wpnt & msg)
  : msg_(msg)
  {}
  Init_Wpnt_yaw y(::global_planner::msg::Wpnt::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Wpnt_yaw(msg_);
  }

private:
  ::global_planner::msg::Wpnt msg_;
};

class Init_Wpnt_x
{
public:
  Init_Wpnt_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Wpnt_y x(::global_planner::msg::Wpnt::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Wpnt_y(msg_);
  }

private:
  ::global_planner::msg::Wpnt msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::global_planner::msg::Wpnt>()
{
  return global_planner::msg::builder::Init_Wpnt_x();
}

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT__BUILDER_HPP_
