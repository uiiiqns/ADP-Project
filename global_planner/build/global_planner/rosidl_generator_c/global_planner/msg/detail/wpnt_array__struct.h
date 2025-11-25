// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_H_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'waypoints'
#include "global_planner/msg/detail/wpnt__struct.h"

/// Struct defined in msg/WpntArray in the package global_planner.
typedef struct global_planner__msg__WpntArray
{
  /// 경로 점들
  global_planner__msg__Wpnt__Sequence waypoints;
} global_planner__msg__WpntArray;

// Struct for a sequence of global_planner__msg__WpntArray.
typedef struct global_planner__msg__WpntArray__Sequence
{
  global_planner__msg__WpntArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} global_planner__msg__WpntArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_H_
