cmake_minimum_required(VERSION 3.8)
project(forzaeth_local_planner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/local_planner_node.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rclcpp_components
  geometry_msgs
  nav_msgs
  visualization_msgs
  std_msgs
)

rclcpp_components_register_nodes(${PROJECT_NAME} "forzaeth_local_planner::LocalPlannerNode")

add_executable(local_planner_main src/main.cpp)
target_link_libraries(local_planner_main ${PROJECT_NAME})

install(
  TARGETS ${PROJECT_NAME} local_planner_main
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  DIRECTORY launch config resource
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_local_planner test/local_planner_test.cpp)
  target_link_libraries(test_local_planner ${PROJECT_NAME})
endif()

ament_package()

