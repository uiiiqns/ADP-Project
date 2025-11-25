// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from global_planner:msg/Metadata.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__METADATA__BUILDER_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__METADATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "global_planner/msg/detail/metadata__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace global_planner
{

namespace msg
{

namespace builder
{

class Init_Metadata_lap_time
{
public:
  explicit Init_Metadata_lap_time(::global_planner::msg::Metadata & msg)
  : msg_(msg)
  {}
  ::global_planner::msg::Metadata lap_time(::global_planner::msg::Metadata::_lap_time_type arg)
  {
    msg_.lap_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::global_planner::msg::Metadata msg_;
};

class Init_Metadata_total_time
{
public:
  explicit Init_Metadata_total_time(::global_planner::msg::Metadata & msg)
  : msg_(msg)
  {}
  Init_Metadata_lap_time total_time(::global_planner::msg::Metadata::_total_time_type arg)
  {
    msg_.total_time = std::move(arg);
    return Init_Metadata_lap_time(msg_);
  }

private:
  ::global_planner::msg::Metadata msg_;
};

class Init_Metadata_average_speed
{
public:
  Init_Metadata_average_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Metadata_total_time average_speed(::global_planner::msg::Metadata::_average_speed_type arg)
  {
    msg_.average_speed = std::move(arg);
    return Init_Metadata_total_time(msg_);
  }

private:
  ::global_planner::msg::Metadata msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::global_planner::msg::Metadata>()
{
  return global_planner::msg::builder::Init_Metadata_average_speed();
}

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__METADATA__BUILDER_HPP_
