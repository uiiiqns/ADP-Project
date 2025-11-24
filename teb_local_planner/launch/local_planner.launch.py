from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
  pkg_share = get_package_share_directory("teb_local_planner")
  config_path = os.path.join(pkg_share, "config", "local_planner.yaml")

  return LaunchDescription(
    [
      Node(
        package="teb_local_planner",
        executable="local_planner_main",
        name="teb_local_planner",
        output="screen",
        parameters=[config_path],
      )
    ]
  )

