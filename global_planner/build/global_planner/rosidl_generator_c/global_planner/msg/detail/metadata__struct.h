// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from global_planner:msg/Metadata.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_H_
#define GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Metadata in the package global_planner.
typedef struct global_planner__msg__Metadata
{
  /// 평균 속도
  float average_speed;
  /// 총 시간
  float total_time;
  /// 랩타임
  float lap_time;
} global_planner__msg__Metadata;

// Struct for a sequence of global_planner__msg__Metadata.
typedef struct global_planner__msg__Metadata__Sequence
{
  global_planner__msg__Metadata * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} global_planner__msg__Metadata__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GLOBAL_PLANNER__MSG__DETAIL__METADATA__STRUCT_H_
