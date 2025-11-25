// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_H_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Wpnt in the package global_planner.
typedef struct global_planner__msg__Wpnt
{
  float x;
  float y;
  /// 차량 방향
  float yaw;
  /// 곡률
  float curvature;
  /// 속도
  float velocity;
} global_planner__msg__Wpnt;

// Struct for a sequence of global_planner__msg__Wpnt.
typedef struct global_planner__msg__Wpnt__Sequence
{
  global_planner__msg__Wpnt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} global_planner__msg__Wpnt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT__STRUCT_H_
