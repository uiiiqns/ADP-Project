#include "forzaeth_local_planner/local_planner_node.hpp"

#include "rclcpp_components/register_node_macro.hpp"

namespace forzaeth_local_planner
{

LocalPlannerNode::LocalPlannerNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("forzaeth_local_planner", options)
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
  route_pub_ = create_publisher<visualization_msgs::msg::MarkerArray>(
    "planner/avoidance/otwpnts", rclcpp::SystemDefaultsQoS());
  latency_pub_ = create_publisher<std_msgs::msg::Float32>(
    "planner/avoidance/latency", rclcpp::SystemDefaultsQoS());
}

void LocalPlannerNode::initialize_subscriptions()
{
  obstacle_sub_ = create_subscription<visualization_msgs::msg::MarkerArray>(
    "perception/obstacles", rclcpp::SensorDataQoS(),
    std::bind(&LocalPlannerNode::on_obstacles, this, std::placeholders::_1));

  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    "car_state/odom", rclcpp::SystemDefaultsQoS(),
    std::bind(&LocalPlannerNode::on_odometry, this, std::placeholders::_1));
}

void LocalPlannerNode::on_timer()
{
  // Placeholder for planner loop. Outputs no real trajectory yet.
  auto latency_msg = std_msgs::msg::Float32();
  latency_msg.data = 0.0F;
  latency_pub_->publish(latency_msg);
}

void LocalPlannerNode::on_obstacles(const visualization_msgs::msg::MarkerArray::SharedPtr msg)
{
  (void)msg;
  // TODO: buffer incoming obstacle markers for planning.
}

void LocalPlannerNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  (void)msg;
  // TODO: store current pose & velocity.
}

}  // namespace forzaeth_local_planner

RCLCPP_COMPONENTS_REGISTER_NODE(forzaeth_local_planner::LocalPlannerNode)

