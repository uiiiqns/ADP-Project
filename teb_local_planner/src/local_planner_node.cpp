#include "teb_local_planner/local_planner_node.hpp"

#include "rclcpp_components/register_node_macro.hpp"

namespace teb_local_planner
{

LocalPlannerNode::LocalPlannerNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("teb_local_planner", options)
{
  load_parameters();
  initialize_publishers();
  initialize_subscriptions();

  timer_ = create_wall_timer(
    std::chrono::milliseconds(static_cast<int>(1000.0 / config_.refresh_hz)),
    std::bind(&LocalPlannerNode::on_timer, this));

  RCLCPP_INFO(get_logger(), "Local planner node initialized with %.2f Hz timer.", config_.refresh_hz);
}

void LocalPlannerNode::load_parameters()
{
  config_.refresh_hz = declare_parameter<double>("refresh_hz", config_.refresh_hz);
  config_.horizon_length = declare_parameter<double>("horizon_length", config_.horizon_length);
  config_.safety_margin = declare_parameter<double>("safety_margin", config_.safety_margin);
}

void LocalPlannerNode::initialize_publishers()
{
  auto qos = rclcpp::QoS(rclcpp::KeepLast(10));

  markers_pub_ = create_publisher<visualization_msgs::msg::MarkerArray>(
    "/planner/avoidance/markers", qos);

  otwpnts_pub_ = create_publisher<f110_msgs::msg::OTWpntArray>(
    "/planner/avoidance/otwpnts", qos);

  considered_obs_pub_ = create_publisher<visualization_msgs::msg::Marker>(
    "/planner/avoidance/considered_OBS", qos);

  propagated_obs_pub_ = create_publisher<visualization_msgs::msg::Marker>(
    "/planner/avoidance/propagated_obs", qos);

  latency_pub_ = create_publisher<std_msgs::msg::Float32>(
    "/planner/avoidance/latency", qos);
}

void LocalPlannerNode::initialize_subscriptions()
{
  auto qos = rclcpp::QoS(rclcpp::KeepLast(10));

  obstacle_sub_ = create_subscription<f110_msgs::msg::ObstacleArray>(
    "/perception/obstacles", qos,
    std::bind(&LocalPlannerNode::obstaclesCallback, this, std::placeholders::_1));

  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    "/car_state/frenet/odom", qos,
    std::bind(&LocalPlannerNode::odomCallback, this, std::placeholders::_1));

  global_wpnts_sub_ = create_subscription<f110_msgs::msg::WpntArray>(
    "/global_waypoints", qos,
    std::bind(&LocalPlannerNode::globalWaypointsCallback, this, std::placeholders::_1));

  global_wpnts_scaled_sub_ = create_subscription<f110_msgs::msg::WpntArray>(
    "/global_waypoints_scaled", qos,
    std::bind(&LocalPlannerNode::scaledWaypointsCallback, this, std::placeholders::_1));
}

void LocalPlannerNode::on_timer()
{
  // Placeholder for planner loop. Outputs no real trajectory yet.
  auto latency_msg = std_msgs::msg::Float32();
  latency_msg.data = 0.0F;
  latency_pub_->publish(latency_msg);
}

void LocalPlannerNode::obstaclesCallback(const f110_msgs::msg::ObstacleArray::SharedPtr msg)
{
  obstacles_ = msg;
}

void LocalPlannerNode::odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  current_state_ = msg;
}

void LocalPlannerNode::globalWaypointsCallback(const f110_msgs::msg::WpntArray::SharedPtr msg)
{
  global_wpnts_ = msg;
}

void LocalPlannerNode::scaledWaypointsCallback(const f110_msgs::msg::WpntArray::SharedPtr msg)
{
  global_wpnts_scaled_ = msg;
}

}  // namespace teb_local_planner

RCLCPP_COMPONENTS_REGISTER_NODE(teb_local_planner::LocalPlannerNode)

