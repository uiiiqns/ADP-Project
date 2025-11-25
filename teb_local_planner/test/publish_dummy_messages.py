#!/usr/bin/env python3
"""
간단한 더미 메시지 발행 스크립트
teb_local_planner가 메시지를 받을 수 있는지 테스트하기 위한 스크립트
"""

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from f110_msgs.msg import WpntArray, Wpnt, ObstacleArray, Obstacle
from std_msgs.msg import Header
import time
import math

class DummyPublisher(Node):
    def __init__(self):
        super().__init__('dummy_publisher')
        
        # Publishers
        self.odom_pub = self.create_publisher(Odometry, '/car_state/frenet/odom', 10)
        self.global_wpnts_pub = self.create_publisher(WpntArray, '/global_waypoints', 10)
        self.scaled_wpnts_pub = self.create_publisher(WpntArray, '/global_waypoints_scaled', 10)
        self.obstacle_pub = self.create_publisher(ObstacleArray, '/perception/obstacles', 10)
        
        # Timer
        self.timer = self.create_timer(0.1, self.publish_messages)  # 10Hz
        
        self.counter = 0
        self.get_logger().info('Dummy publisher started. Publishing test messages...')
    
    def publish_messages(self):
        now = self.get_clock().now()
        
        # 1. Odometry 메시지 발행
        odom = Odometry()
        odom.header.stamp = now.to_msg()
        odom.header.frame_id = "map"
        odom.pose.pose.position.x = 5.0  # s 좌표 (현재 위치)
        odom.pose.pose.position.y = 0.0   # d 좌표
        odom.twist.twist.linear.x = 5.0    # 속도
        self.odom_pub.publish(odom)
        
        # 2. Global Waypoints 메시지 발행 (더 많은 웨이포인트)
        wpnts = WpntArray()
        wpnts.header.stamp = now.to_msg()
        wpnts.header.frame_id = "map"
        
        # 50개 웨이포인트 생성 (원형 경로)
        num_wpnts = 50
        for i in range(num_wpnts):
            wpnt = Wpnt()
            wpnt.id = i
            wpnt.s_m = float(i * 0.5)  # 0.5m 간격
            angle = float(i) * 2.0 * math.pi / num_wpnts
            wpnt.x_m = 10.0 * math.cos(angle)
            wpnt.y_m = 10.0 * math.sin(angle)
            wpnt.psi_rad = angle + math.pi / 2.0  # 방향
            wpnt.vx_mps = 5.0
            wpnt.kappa_radpm = 0.1  # 곡률
            wpnt.d_left = -2.0  # 왼쪽 경계
            wpnt.d_right = 2.0  # 오른쪽 경계
            wpnts.wpnts.append(wpnt)
        
        self.global_wpnts_pub.publish(wpnts)
        self.scaled_wpnts_pub.publish(wpnts)  # 같은 내용으로 scaled도 발행
        
        # 3. 장애물 메시지 발행 (테스트용)
        if self.counter % 10 == 0:  # 1초마다 발행
            obstacles = ObstacleArray()
            obstacles.header.stamp = now.to_msg()
            obstacles.header.frame_id = "map"
            
            # 테스트 장애물 하나 생성 (경로 앞에)
            obs = Obstacle()
            obs.s_center = 8.0  # 현재 위치(s=5.0) 앞 3m
            obs.d_center = 0.5  # 경로에서 약간 오른쪽
            obs.s_start = 7.5
            obs.s_end = 8.5
            obs.d_left = 0.0
            obs.d_right = 1.0
            obs.vs = 0.0  # 정지한 장애물
            obs.vd = 0.0
            obstacles.obstacles.append(obs)
            
            self.obstacle_pub.publish(obstacles)
            self.get_logger().info(f'Published obstacle at s={obs.s_center}, d={obs.d_center}')
        
        self.counter += 1

def main(args=None):
    rclpy.init(args=args)
    node = DummyPublisher()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()


