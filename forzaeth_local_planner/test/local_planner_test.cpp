#include <gtest/gtest.h>

#include "forzaeth_local_planner/local_planner_node.hpp"

TEST(LocalPlannerNodeTest, InitializesWithDefaults)
{
  rclcpp::init(0, nullptr);
  {
    auto node = std::make_shared<forzaeth_local_planner::LocalPlannerNode>();
    EXPECT_TRUE(node->get_parameter("refresh_hz").as_double() > 0.0);
  }
  rclcpp::shutdown();
}

