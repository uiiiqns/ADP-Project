#include "forzaeth_local_planner/local_planner_node.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<forzaeth_local_planner::LocalPlannerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

