cmake_minimum_required(VERSION 3.5)
project(global_planner)

# ROS2 의존성 패키지
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# 메시지 파일 처리
find_package(rosidl_default_generators REQUIRED)

# 메시지 파일 생성
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Wpnt.msg"
  "msg/WpntArray.msg"
  "msg/Metadata.msg"
)

# Include 디렉토리 설정
include_directories(include)

add_library(utils_lib src/utils.cpp)
target_include_directories(utils_lib PUBLIC
	include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
	$<INSTALL_INTERFACE:include>
)

ament_target_dependencies(utils_lib
	rclcpp
)

# 소스 파일 추가
add_executable(global_planner_node src/global_planner_node.cpp)
add_executable(centerline_extractor src/centerline_extractor.cpp)
add_executable(curvature_planner src/curvature_planner.cpp)
add_executable(velocity_planner src/velocity_planner.cpp)
add_executable(time_optimal_planner src/time_optimal_planner.cpp)

# ROS2 의존성 연결
ament_target_dependencies(global_planner_node 
  rclcpp 
  std_msgs 
  sensor_msgs 
  nav_msgs 
  geometry_msgs
  )

ament_target_dependencies(centerline_extractor 
  rclcpp 
  nav_msgs
  )

ament_target_dependencies(curvature_planner 
  rclcpp 
  )

ament_target_dependencies(velocity_planner 
  rclcpp 
  )

ament_target_dependencies(time_optimal_planner 
  rclcpp )

# Utils 라이브러리 링크
target_link_libraries(centerline_extractor utils_lib)
target_link_libraries(curvature_planner utils_lib)
target_link_libraries(velocity_planner utils_lib)
target_link_libraries(time_optimal_planner utils_lib)
target_link_libraries(global_planner_node utils_lib)

# 메시지 타겟 의존성 추가
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(global_planner_node "${cpp_typesupport_target}")
target_link_libraries(centerline_extractor "${cpp_typesupport_target}")
target_link_libraries(curvature_planner "${cpp_typesupport_target}")
target_link_libraries(velocity_planner "${cpp_typesupport_target}")
target_link_libraries(time_optimal_planner "${cpp_typesupport_target}")



# 설치
install(TARGETS
  global_planner_node
  centerline_extractor
  curvature_planner
  velocity_planner
  time_optimal_planner
  utils_lib
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include
)

ament_package()
