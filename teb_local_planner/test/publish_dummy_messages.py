#!/usr/bin/env python3
"""
간단한 더미 메시지 발행 스크립트
teb_local_planner가 메시지를 받을 수 있는지 테스트하기 위한 스크립트
"""

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from f110_msgs.msg import WpntArray, Wpnt
from std_msgs.msg import Header
import time

class DummyPublisher(Node):
    def __init__(self):
        super().__init__('dummy_publisher')
        
        # Publishers
        self.odom_pub = self.create_publisher(Odometry, '/car_state/frenet/odom', 10)
        self.global_wpnts_pub = self.create_publisher(WpntArray, '/global_waypoints', 10)
        self.scaled_wpnts_pub = self.create_publisher(WpntArray, '/global_waypoints_scaled', 10)
        
        # Timer
        self.timer = self.create_timer(0.1, self.publish_messages)  # 10Hz
        
        self.get_logger().info('Dummy publisher started. Publishing test messages...')
    
    def publish_messages(self):
        now = self.get_clock().now()
        
        # 1. Odometry 메시지 발행
        odom = Odometry()
        odom.header.stamp = now.to_msg()
        odom.header.frame_id = "map"
        odom.pose.pose.position.x = 10.0  # s 좌표
        odom.pose.pose.position.y = 0.0   # d 좌표
        odom.twist.twist.linear.x = 5.0    # 속도
        self.odom_pub.publish(odom)
        
        # 2. Global Waypoints 메시지 발행
        wpnts = WpntArray()
        wpnts.header.stamp = now.to_msg()
        wpnts.header.frame_id = "map"
        
        # 간단한 웨이포인트 10개 생성
        for i in range(10):
            wpnt = Wpnt()
            wpnt.id = i
            wpnt.s_m = float(i * 2.0)  # 2m 간격
            wpnt.x_m = float(i * 2.0)
            wpnt.y_m = 0.0
            wpnt.vx_mps = 5.0
            wpnts.wpnts.append(wpnt)
        
        self.global_wpnts_pub.publish(wpnts)
        self.scaled_wpnts_pub.publish(wpnts)  # 같은 내용으로 scaled도 발행

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


