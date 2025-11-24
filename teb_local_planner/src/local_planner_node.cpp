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
  
  wait_for_messages();

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

  // 새로 추가할 파라미터들
  config_.from_bag = declare_parameter<bool>("from_bag", config_.from_bag);
  config_.measure = declare_parameter<bool>("measure", config_.measure);
  
  config_.pre_apex_0 = declare_parameter<double>("pre_apex_0", std::abs(config_.pre_apex_0));
  config_.pre_apex_1 = declare_parameter<double>("pre_apex_1", std::abs(config_.pre_apex_1));
  config_.pre_apex_2 = declare_parameter<double>("pre_apex_2", std::abs(config_.pre_apex_2));
  config_.post_apex_0 = declare_parameter<double>("post_apex_0", config_.post_apex_0);
  config_.post_apex_1 = declare_parameter<double>("post_apex_1", config_.post_apex_1);
  config_.post_apex_2 = declare_parameter<double>("post_apex_2", config_.post_apex_2);
  
  config_.evasion_dist = declare_parameter<double>("evasion_dist", config_.evasion_dist);
  config_.obs_traj_tresh = declare_parameter<double>("obs_traj_tresh", config_.obs_traj_tresh);
  config_.spline_bound_mindist = declare_parameter<double>("spline_bound_mindist", config_.spline_bound_mindist);
  config_.fixed_pred_time = declare_parameter<double>("fixed_pred_time", config_.fixed_pred_time);
  config_.kd_obs_pred = declare_parameter<double>("kd_obs_pred", config_.kd_obs_pred);
  config_.lookahead = declare_parameter<double>("lookahead", config_.lookahead);
  
  // pre_apex는 음수로 저장 (Python 코드 참고)
  config_.pre_apex_0 = -std::abs(config_.pre_apex_0);
  config_.pre_apex_1 = -std::abs(config_.pre_apex_1);
  config_.pre_apex_2 = -std::abs(config_.pre_apex_2);
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
  // Frenet 좌표계에서 s, d, vs 추출
  cur_s_ = msg->pose.pose.position.x;   // s 좌표
  cur_d_ = msg->pose.pose.position.y;    // d 좌표
  cur_vs_ = msg->twist.twist.linear.x;   // 속도
}

void LocalPlannerNode::globalWaypointsCallback(const f110_msgs::msg::WpntArray::SharedPtr msg)
{
  global_wpnts_ = msg;

  if (msg && !msg->wpnts.empty()) {
    // 최대 속도 계산
    gb_vmax_ = 0.0;
    for (const auto& wpnt : msg->wpnts) {
      if (wpnt.vx_mps > gb_vmax_) {
        gb_vmax_ = wpnt.vx_mps;
      }
    }
    
    // 최대 인덱스와 최대 s 값
    gb_max_idx_ = msg->wpnts.back().id;
    gb_max_s_ = msg->wpnts.back().s_m;
  }
}

void LocalPlannerNode::scaledWaypointsCallback(const f110_msgs::msg::WpntArray::SharedPtr msg)
{
  global_wpnts_scaled_ = msg;
}

void LocalPlannerNode::wait_for_messages()
{
  RCLCPP_INFO(get_logger(), "Waiting for required messages...");
  
  bool state_received = false;
  bool gb_received = false;
  bool scaled_gb_received = false;
  
  rclcpp::Rate rate(10); // 10Hz로 체크
  
  while (rclcpp::ok() && (!state_received || !gb_received || !scaled_gb_received)) {
    rclcpp::spin_some(shared_from_this());
    
    if (current_state_ && !state_received) {
      RCLCPP_INFO(get_logger(), "Received State message.");
      state_received = true;
    }
    
    if (global_wpnts_ && !gb_received) {
      RCLCPP_INFO(get_logger(), "Received Global Waypoints message.");
      gb_received = true;
    }
    
    if (global_wpnts_scaled_ && !scaled_gb_received) {
      RCLCPP_INFO(get_logger(), "Received Scaled Global Waypoints message.");
      scaled_gb_received = true;
    }
    
    rate.sleep();
  }
  
  RCLCPP_INFO(get_logger(), "All required messages received. Continuing...");
}

}  // namespace teb_local_planner

RCLCPP_COMPONENTS_REGISTER_NODE(teb_local_planner::LocalPlannerNode)

