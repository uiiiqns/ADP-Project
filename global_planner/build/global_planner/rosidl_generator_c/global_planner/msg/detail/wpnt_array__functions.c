// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice
#include "global_planner/msg/detail/wpnt_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `waypoints`
#include "global_planner/msg/detail/wpnt__functions.h"

bool
global_planner__msg__WpntArray__init(global_planner__msg__WpntArray * msg)
{
  if (!msg) {
    return false;
  }
  // waypoints
  if (!global_planner__msg__Wpnt__Sequence__init(&msg->waypoints, 0)) {
    global_planner__msg__WpntArray__fini(msg);
    return false;
  }
  return true;
}

void
global_planner__msg__WpntArray__fini(global_planner__msg__WpntArray * msg)
{
  if (!msg) {
    return;
  }
  // waypoints
  global_planner__msg__Wpnt__Sequence__fini(&msg->waypoints);
}

bool
global_planner__msg__WpntArray__are_equal(const global_planner__msg__WpntArray * lhs, const global_planner__msg__WpntArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // waypoints
  if (!global_planner__msg__Wpnt__Sequence__are_equal(
      &(lhs->waypoints), &(rhs->waypoints)))
  {
    return false;
  }
  return true;
}

bool
global_planner__msg__WpntArray__copy(
  const global_planner__msg__WpntArray * input,
  global_planner__msg__WpntArray * output)
{
  if (!input || !output) {
    return false;
  }
  // waypoints
  if (!global_planner__msg__Wpnt__Sequence__copy(
      &(input->waypoints), &(output->waypoints)))
  {
    return false;
  }
  return true;
}

global_planner__msg__WpntArray *
global_planner__msg__WpntArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__WpntArray * msg = (global_planner__msg__WpntArray *)allocator.allocate(sizeof(global_planner__msg__WpntArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(global_planner__msg__WpntArray));
  bool success = global_planner__msg__WpntArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
global_planner__msg__WpntArray__destroy(global_planner__msg__WpntArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    global_planner__msg__WpntArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
global_planner__msg__WpntArray__Sequence__init(global_planner__msg__WpntArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__WpntArray * data = NULL;

  if (size) {
    data = (global_planner__msg__WpntArray *)allocator.zero_allocate(size, sizeof(global_planner__msg__WpntArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = global_planner__msg__WpntArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        global_planner__msg__WpntArray__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
global_planner__msg__WpntArray__Sequence__fini(global_planner__msg__WpntArray__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      global_planner__msg__WpntArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

global_planner__msg__WpntArray__Sequence *
global_planner__msg__WpntArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__WpntArray__Sequence * array = (global_planner__msg__WpntArray__Sequence *)allocator.allocate(sizeof(global_planner__msg__WpntArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = global_planner__msg__WpntArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
global_planner__msg__WpntArray__Sequence__destroy(global_planner__msg__WpntArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    global_planner__msg__WpntArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
global_planner__msg__WpntArray__Sequence__are_equal(const global_planner__msg__WpntArray__Sequence * lhs, const global_planner__msg__WpntArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!global_planner__msg__WpntArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
global_planner__msg__WpntArray__Sequence__copy(
  const global_planner__msg__WpntArray__Sequence * input,
  global_planner__msg__WpntArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(global_planner__msg__WpntArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    global_planner__msg__WpntArray * data =
      (global_planner__msg__WpntArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!global_planner__msg__WpntArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          global_planner__msg__WpntArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!global_planner__msg__WpntArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
