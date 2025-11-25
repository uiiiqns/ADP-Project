// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from global_planner:msg/Metadata.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__METADATA__TRAITS_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__METADATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "global_planner/msg/detail/metadata__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace global_planner
{

namespace msg
{

inline void to_flow_style_yaml(
  const Metadata & msg,
  std::ostream & out)
{
  out << "{";
  // member: average_speed
  {
    out << "average_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.average_speed, out);
    out << ", ";
  }

  // member: total_time
  {
    out << "total_time: ";
    rosidl_generator_traits::value_to_yaml(msg.total_time, out);
    out << ", ";
  }

  // member: lap_time
  {
    out << "lap_time: ";
    rosidl_generator_traits::value_to_yaml(msg.lap_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Metadata & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: average_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "average_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.average_speed, out);
    out << "\n";
  }

  // member: total_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_time: ";
    rosidl_generator_traits::value_to_yaml(msg.total_time, out);
    out << "\n";
  }

  // member: lap_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lap_time: ";
    rosidl_generator_traits::value_to_yaml(msg.lap_time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Metadata & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace global_planner

namespace rosidl_generator_traits
{

[[deprecated("use global_planner::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const global_planner::msg::Metadata & msg,
  std::ostream & out, size_t indentation = 0)
{
  global_planner::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use global_planner::msg::to_yaml() instead")]]
inline std::string to_yaml(const global_planner::msg::Metadata & msg)
{
  return global_planner::msg::to_yaml(msg);
}

template<>
inline const char * data_type<global_planner::msg::Metadata>()
{
  return "global_planner::msg::Metadata";
}

template<>
inline const char * name<global_planner::msg::Metadata>()
{
  return "global_planner/msg/Metadata";
}

template<>
struct has_fixed_size<global_planner::msg::Metadata>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<global_planner::msg::Metadata>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<global_planner::msg::Metadata>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // GLOBAL_PLANNER__MSG__DETAIL__METADATA__TRAITS_HPP_
