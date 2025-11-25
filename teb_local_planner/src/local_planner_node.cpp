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
  RCLCPP_INFO(get_logger(), "Waiting for required messages...");
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
  // 메시지가 준비될 때까지 대기
  if (!messages_ready_) {
    messages_ready_ = check_messages_ready();
    if (!messages_ready_) {
      return;  // 아직 메시지가 없으면 리턴
    }
    RCLCPP_INFO(get_logger(), "All required messages received. Starting planner...");
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  // 입력 데이터 유효성 검사
  if (!obstacles_ || !global_wpnts_scaled_ || !current_state_){
    return;
  }
  
  std::vector<f110_msgs::msg::Obstacle> close_obstacles = filter_obstacles();

  f110_msgs::msg::OTWpntArray wpnts;
  visualization_msgs::msg::MarkerArray markers;

  if (!close_obstacles.empty()){
    auto closest_obs = find_closest_obstacle(close_obstacles);

    std::tie(wpnts, markers) = generate_evasion_trajectory(closest_obs);
  }else{
    markers = create_delete_all_marker();
  }

  otwpnts_pub_->publish(wpnts);
  markers_pub_->publish(markers);

  if(config_.measure){
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000.0;

    std_msgs::msg::Float32 latency_msg;
    latency_msg.data = static_cast<float>(duration);
    latency_pub_->publish(latency_msg);
  }
}

std::vector<f110_msgs::msg::Obstacle> LocalPlannerNode::filter_obstacles(){
  std::vector<f110_msgs::msg::Obstacle> close_obstacles;

  if(!obstacles_ || obstacles_->obstacles.empty()){
    return close_obstacles;
  }

  for(const auto& obs : obstacles_->obstacles){
    if(std::abs(obs.d_center) > config_.obs_traj_tresh){
      continue;
    }

    auto predicted_obs = predict_obstacle_movement(obs);

    double dist_in_front = (predicted_obs.s_center - cur_s_);
    if(dist_in_front < 0){
      dist_in_front += gb_max_s_;
    }

    if(dist_in_front < config_.lookahead && dist_in_front > 0){
      close_obstacles.push_back(predicted_obs);
    }
  }

  return close_obstacles;
}

f110_msgs::msg::Obstacle LocalPlannerNode::find_closest_obstacle(const std::vector<f110_msgs::msg::Obstacle>& obstacles){
  if(obstacles.empty()){
    return f110_msgs::msg::Obstacle();
  }

  auto closest = std::min_element(obstacles.begin(), obstacles.end(),
   [this](const f110_msgs::msg::Obstacle& a, const f110_msgs::msg::Obstacle& b){
      double dist_a = (a.s_center - cur_s_);
      if(dist_a < 0) dist_a += gb_max_s_;

      double dist_b = (b.s_center - cur_s_);
      if(dist_b < 0) dist_b += gb_max_s_;

      return dist_a < dist_b;
    });

  return *closest;
}

f110_msgs::msg::Obstacle LocalPlannerNode::predict_obstacle_movement(
  const f110_msgs::msg::Obstacle& obs)
{
  f110_msgs::msg::Obstacle predicted = obs;
  
  // 간단한 constant velocity 모델 사용
  if ((obs.s_center - cur_s_) < 10.0) {  // TODO: 파라미터로 만들기
    double delta_s = config_.fixed_pred_time * obs.vs;
    double delta_d = config_.fixed_pred_time * obs.vd;
    
    predicted.s_start += delta_s;
    predicted.s_center += delta_s;
    predicted.s_end += delta_s;
    
    // Wraparound 처리
    predicted.s_start = std::fmod(predicted.s_start + gb_max_s_, gb_max_s_);
    predicted.s_center = std::fmod(predicted.s_center + gb_max_s_, gb_max_s_);
    predicted.s_end = std::fmod(predicted.s_end + gb_max_s_, gb_max_s_);
    
    predicted.d_left += delta_d;
    predicted.d_center += delta_d;
    predicted.d_right += delta_d;
    
    // 예측된 장애물 위치 마커 발행
    // TODO: 시각화 마커 생성
  }
  
  return predicted;
}

std::pair<f110_msgs::msg::OTWpntArray, visualization_msgs::msg::MarkerArray>
LocalPlannerNode::generate_evasion_trajectory(
  const f110_msgs::msg::Obstacle& obstacle)
{
  f110_msgs::msg::OTWpntArray wpnts;
  visualization_msgs::msg::MarkerArray markers;
  
  // TODO: TEB 알고리즘 구현
  // 지금은 기본 구조만 만들기
  
  wpnts.header.stamp = now();
  wpnts.header.frame_id = "map";
  
  // 가장 가까운 장애물 마커 발행
  // TODO: considered_OBS 마커 생성
  
  return std::make_pair(wpnts, markers);
}

visualization_msgs::msg::MarkerArray LocalPlannerNode::create_delete_all_marker()
{
  visualization_msgs::msg::MarkerArray markers;
  visualization_msgs::msg::Marker del_mrk;
  
  del_mrk.header.stamp = now();
  del_mrk.header.frame_id = "map";
  del_mrk.action = visualization_msgs::msg::Marker::DELETEALL;
  
  markers.markers.push_back(del_mrk);
  return markers;
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

bool LocalPlannerNode::check_messages_ready()
{
  static bool state_logged = false;
  static bool gb_logged = false;
  static bool scaled_gb_logged = false;
  
  bool state_ready = (current_state_ != nullptr);
  bool gb_ready = (global_wpnts_ != nullptr && !global_wpnts_->wpnts.empty());
  bool scaled_gb_ready = (global_wpnts_scaled_ != nullptr);
  
  if (state_ready && !state_logged) {
    RCLCPP_INFO(get_logger(), "Received State message.");
    state_logged = true;
  }
  
  if (gb_ready && !gb_logged) {
    RCLCPP_INFO(get_logger(), "Received Global Waypoints message.");
    gb_logged = true;
  }
  
  if (scaled_gb_ready && !scaled_gb_logged) {
    RCLCPP_INFO(get_logger(), "Received Scaled Global Waypoints message.");
    scaled_gb_logged = true;
  }
  
  return state_ready && gb_ready && scaled_gb_ready;
}

}  // namespace teb_local_planner

RCLCPP_COMPONENTS_REGISTER_NODE(teb_local_planner::LocalPlannerNode)

