# 타임 최적화 플래너를 실행하는 별도의 launch 파일

import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('planner_type', default_value='laptime', description='Select the planner type (curvature/laptime)'),
        
        LogInfo(condition=LaunchConfiguration('planner_type'), msg="Starting minimal laptime planner..."),

        # 랩타임 플래너 노드 실행
        Node(
            package='global_planner',
            executable='global_planner_node',
            output='screen',
            parameters=[{'planner_type': LaunchConfiguration('planner_type')}]
        ),
    ])
