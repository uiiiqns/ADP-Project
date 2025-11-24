#pragma once

#include <memory>
#include <string>
#include <vector>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "std_msgs/msg/float32.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

#include "rclcpp/rclcpp.hpp"

namespace forzaeth_local_planner
{

struct PlannerConfig
{
  double refresh_hz{20.0};
  double horizon_length{10.0};
  double safety_margin{0.2};
};

class LocalPlannerNode : public rclcpp::Node
{
public:
  explicit LocalPlannerNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  void initialize_publishers();
  void initialize_subscriptions();
  void load_parameters();

  void on_timer();
  void on_obstacles(const visualization_msgs::msg::MarkerArray::SharedPtr msg);
  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);

  PlannerConfig config_;
  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr obstacle_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr route_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr latency_pub_;
};

}  // namespace forzaeth_local_planner

