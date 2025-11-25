# TEB Local Planner 프로젝트 요약

## 📌 프로젝트 개요
- **목표:** Elastic Bands 기반 TEB (Timed Elastic Band) 로컬 플래너 구현
- **환경:** ROS2 Humble, C++, Ubuntu 22.04
- **패키지명:** `teb_local_planner`
- **위치:** `/home/subin/Desktop/subin/ADP-Project/ADP-Project/teb_local_planner/`

## ✅ 완료된 작업

### 1. 패키지 기본 구조
- ROS2 패키지 생성 (CMakeLists.txt, package.xml)
- 노드 클래스 구조 (`LocalPlannerNode`)
- 런치 파일 및 설정 파일

### 2. 토픽 인터페이스
**구독 (4개):**
- `/perception/obstacles` (f110_msgs/ObstacleArray)
- `/car_state/frenet/odom` (nav_msgs/Odometry)
- `/global_waypoints` (f110_msgs/WpntArray)
- `/global_waypoints_scaled` (f110_msgs/WpntArray)

**발행 (5개):**
- `/planner/avoidance/markers` (visualization_msgs/MarkerArray)
- `/planner/avoidance/otwpnts` (f110_msgs/OTWpntArray)
- `/planner/avoidance/considered_OBS` (visualization_msgs/Marker)
- `/planner/avoidance/propagated_obs` (visualization_msgs/Marker)
- `/planner/avoidance/latency` (std_msgs/Float32)

### 3. 데이터 버퍼/상태 구조
- 현재 차량 상태 변수 (cur_s_, cur_d_, cur_vs_)
- 전역 경로 정보 (gb_vmax_, gb_max_idx_, gb_max_s_)
- 메시지 대기 로직 (`check_messages_ready()`)

### 4. 파라미터 선언
- 기본 파라미터 (refresh_hz, horizon_length, safety_margin)
- Spline 파라미터 (pre_apex_*, post_apex_*)
- 장애물 회피 파라미터 (evasion_dist, obs_traj_tresh 등)
- TEB 파라미터 (lookahead)

### 5. 메인 루프 구현
- `on_timer()` - 20Hz 메인 루프
- `filter_obstacles()` - 장애물 필터링
- `find_closest_obstacle()` - 가장 가까운 장애물 선택
- `predict_obstacle_movement()` - 장애물 위치 예측

### 6. TEB 알고리즘 구현
- `TEB` 클래스 생성
- `TEBPose` 구조체 (위치 + 방향 + 시간 + 반경)
- 6가지 힘 계산 함수:
  - `contraction_force()` - 수축력
  - `repulsive_force()` - 반발력
  - `velocity_constraint_force()` - 속도 제약
  - `acceleration_constraint_force()` - 가속도 제약
  - `nonholonomic_constraint_force()` - 비홀로노믹 제약
  - `turning_radius_constraint_force()` - 회전 반경 제약
- `update_poses()` - 포즈 업데이트
- `optimize()` - 최적화 반복

### 7. 경로 생성
- `generate_evasion_trajectory()` - TEB를 사용한 회피 경로 생성
- `get_initial_path_from_global()` - 전역 경로에서 초기 경로 추출
- `convert_obstacle_to_points()` - 장애물을 포인트로 변환

## 📁 핵심 파일

### 헤더 파일
- `include/teb_local_planner/local_planner_node.hpp` - 노드 클래스
- `include/teb_local_planner/teb.hpp` - TEB 알고리즘 클래스

### 구현 파일
- `src/local_planner_node.cpp` - 노드 구현
- `src/teb.cpp` - TEB 알고리즘 구현
- `src/main.cpp` - 메인 엔트리 포인트

### 설정 파일
- `config/local_planner.yaml` - 파라미터 설정
- `launch/local_planner.launch.py` - 런치 파일

## 🔧 의존성
- `rclcpp`, `rclcpp_components`
- `geometry_msgs`, `nav_msgs`, `visualization_msgs`, `std_msgs`
- `f110_msgs`
- `Eigen3`

## 🚀 빌드 및 실행

```bash
cd ~/forza_ws/race_stack
colcon build --packages-select teb_local_planner --symlink-install
source install/setup.bash
ros2 launch teb_local_planner local_planner.launch.py
```

## 📝 주요 알고리즘

### TEB 최적화 과정
1. 초기 경로 생성 (전역 경로에서)
2. 장애물을 포인트로 변환
3. TEB 객체 생성
4. 50번 반복 최적화:
   - 6가지 힘 계산
   - 포즈 업데이트
   - 시간 간격 최적화
5. 최적화된 경로 반환

### 핵심 수식
- **Equation (7):** 비홀로노믹 제약 `h_k = (dir_i + dir_i1) · d_k = 0`
- **Equation (8):** 회전 반경 `ρ_k = ||d_k||_2 / (2 * sin(Δβ_k / 2))`
- **Equation (9):** 목적 함수 `V(B) = Σ (f_v + f_a + f_obs + f_path + f_t + f_nh + f_r)`

## ⚠️ 알려진 이슈 / TODO

1. **Frenet 변환:** 현재는 간단한 근사 사용, 실제 FrenetConverter 사용 필요
2. **파라미터 튜닝:** 가중치들(kv, ka, knh 등)을 파라미터로 외부화
3. **최적화 알고리즘:** 현재는 gradient descent, 더 고급 알고리즘 적용 가능
4. **장애물 예측:** 더 정교한 예측 모델 추가

## 📚 참고 문서
- `TEB_IMPLEMENTATION.md` - 상세 구현 설명
- `PPT_KEY_CODE.md` - PPT용 핵심 코드 정리

## 🔗 Git 정보
- **브랜치:** Subin
- **저장소:** ADP-Project
- **최근 커밋:** "~4 step" - 메인 루프 구현

## 💡 다음 단계
1. 실제 레이스 스택과 통합 테스트
2. 파라미터 튜닝
3. 성능 최적화
4. Frenet 변환 통합



