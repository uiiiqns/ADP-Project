# TEB 알고리즘 구현 설명서

## 📋 전체 구조 개요

이 구현은 **Elastic Bands 알고리즘**을 기반으로 **Timed Elastic Band (TEB)** 기능을 추가한 것입니다.

### 파일 구조
```
teb_local_planner/
├── include/teb_local_planner/
│   ├── local_planner_node.hpp  # ROS2 노드 클래스
│   └── teb.hpp                 # TEB 알고리즘 클래스
├── src/
│   ├── local_planner_node.cpp  # 노드 구현
│   ├── teb.cpp                 # TEB 알고리즘 구현
│   └── main.cpp                # 메인 엔트리 포인트
└── CMakeLists.txt
```

---

## 🔄 전체 실행 흐름

### 1단계: 노드 초기화
```
LocalPlannerNode 생성자
  ↓
load_parameters()        # 파라미터 로드
  ↓
initialize_publishers()  # 퍼블리셔 생성
  ↓
initialize_subscriptions() # 구독자 생성
  ↓
타이머 시작 (20Hz)
```

### 2단계: 메인 루프 (on_timer)
```
on_timer() (20Hz로 호출)
  ↓
check_messages_ready()  # 메시지 대기
  ↓
filter_obstacles()      # 가까운 장애물만 필터링
  ↓
find_closest_obstacle()  # 가장 가까운 장애물 선택
  ↓
generate_evasion_trajectory()  # 회피 경로 생성 (TEB 사용)
  ↓
결과 발행 (waypoints + markers)
```

### 3단계: TEB 경로 생성
```
generate_evasion_trajectory()
  ↓
get_initial_path_from_global()  # 전역 경로에서 초기 경로 추출
  ↓
convert_obstacle_to_points()     # 장애물을 포인트로 변환
  ↓
TEB 객체 생성
  ↓
teb.optimize(50)                # 50번 반복 최적화
  ↓
get_path_with_velocities()      # 최적화된 경로 + 속도 반환
  ↓
Waypoint 배열로 변환
```

---

## 🧩 핵심 클래스 설명

### 1. TEBPose (포즈 구조체)
**역할:** Elastic Bands의 Bubble을 확장한 개념

```cpp
struct TEBPose {
  Eigen::Vector2d pos;    // 위치 [x, y]
  double theta;            // 방향 β (rad)
  double delta_t;          // 시간 간격 ΔT (sec)
  double radius;           // 안전 반경 (장애물까지 거리)
};
```

**비교:**
- **Elastic Bands Bubble:** 위치 + 반경만
- **TEB Pose:** 위치 + 방향 + 시간 + 반경

---

### 2. TEB 클래스 (핵심 알고리즘)

#### 생성자
```cpp
TEB(initial_path, obstacles, v_max, a_max, rho_min, wheelbase)
```
- `initial_path`: 초기 경로 (전역 경로에서 가져옴)
- `obstacles`: 장애물 위치들
- `v_max`: 최대 속도
- `a_max`: 최대 가속도
- `rho_min`: 최소 회전 반경
- `wheelbase`: 차량 휠베이스

#### 최적화 과정
```
optimize(max_iter=50)
  ↓
for (50번 반복) {
  update_poses()  # 각 포즈 업데이트
}
```

---

## 🔧 힘(Force) 계산 함수들

### Elastic Bands 기본 힘들

#### 1. `contraction_force(i)` - 수축력
**목적:** 인접한 포즈들을 가깝게 만듦

```
f_c = kc * ( (prev-current)/|prev-current| + (next-current)/|next-current| )
```

**의미:**
- 이전 포즈와 다음 포즈가 현재 포즈를 당기는 힘
- 경로를 짧고 부드럽게 만듦

#### 2. `repulsive_force(i)` - 반발력
**목적:** 장애물로부터 멀어지게 함

```
f_r = kr * (rho0 - rho) * grad(ρ)
```

**의미:**
- `rho`: 현재 위치에서 장애물까지 거리
- `rho0`: 최대 반발력 적용 거리 (20m)
- `grad(ρ)`: 거리 필드의 그래디언트 (장애물 방향)

---

### TEB 추가 힘들

#### 3. `velocity_constraint_force(i)` - 속도 제약
**목적:** 최대 속도를 초과하지 않도록

```cpp
v = ||pos[i+1] - pos[i]|| / ΔT
if (v > v_max) {
  return -kv * (v - v_max) * direction
}
```

**의미:**
- 속도가 너무 크면 속도를 줄이는 방향으로 힘 적용

#### 4. `acceleration_constraint_force(i)` - 가속도 제약
**목적:** 최대 가속도를 초과하지 않도록

```cpp
a = (v[i+1] - v[i]) / ΔT
if (|a| > a_max) {
  return -ka * sign(a) * (|a| - a_max) * direction
}
```

**의미:**
- 가속도가 너무 크면 가속도를 줄이는 방향으로 힘 적용

#### 5. `nonholonomic_constraint_force(i)` - 비홀로노믹 제약
**목적:** 차량이 같은 곡률의 호 위에서 움직이도록

**Equation (7):**
```
h_k = (dir_i + dir_i1) · d_k ≈ 0
```

**의미:**
- 연속된 두 포즈가 같은 곡률의 호 위에 있어야 함
- 차량은 옆으로 움직일 수 없음

#### 6. `turning_radius_constraint_force(i)` - 최소 회전 반경 제약
**목적:** 최소 회전 반경보다 작게 회전하지 않도록

**Equation (8):**
```
ρ_k = ||d_k||_2 / (2 * sin(Δβ_k / 2))
```

**제약:**
```
ρ_k ≥ ρ_min
```

**의미:**
- 회전 반경이 너무 작으면 곡률을 줄이는 방향으로 힘 적용

---

## 🔄 포즈 업데이트 과정

### `update_poses()` 함수

```cpp
for (각 포즈 i) {
  // 1. 모든 힘 합산
  f_total = 
    contraction_force(i) +           // 경로 단축
    repulsive_force(i) +              // 장애물 회피
    velocity_constraint_force(i) +    // 속도 제약
    acceleration_constraint_force(i) + // 가속도 제약
    nonholonomic_constraint_force(i) + // 비홀로노믹 제약
    turning_radius_constraint_force(i); // 회전 반경 제약
  
  // 2. 접선 방향 제거 (Elastic Bands 방식)
  f_star = f_total - (f_total · v) * v / ||v||^2
  
  // 3. 적응형 스텝 크기로 위치 업데이트
  new_pos = pos[i] + radius[i] * f_star
  
  // 4. 시간 간격 최적화
  new_dt = optimize_time_interval(i)
  
  // 5. 방향 업데이트
  update_orientation(i)
  
  // 6. 새로운 반경 계산
  new_radius = compute_rho(new_pos)
}
```

**핵심 포인트:**
- **접선 방향 제거:** 경로를 따라 움직이는 성분을 제거하여 경로 형태를 유지
- **적응형 스텝:** 안전 반경을 스텝 크기로 사용 (장애물이 가까우면 작게 이동)
- **시간 최적화:** 속도 제약을 만족하는 최소 시간 계산

---

## 📊 시간 최적화

### `optimize_time_interval(i)`

```cpp
optimal_dt = distance / v_max
```

**목적:**
- 시간을 최소화하면서 속도 제약 만족
- Equation (2): `min Σ ΔT_k^2`

**의미:**
- 빠르게 이동하면서도 제약을 만족하는 시간 간격 계산

---

## 🔗 함수 연결 관계도

```
LocalPlannerNode::on_timer()
  │
  ├─→ filter_obstacles()
  │     └─→ predict_obstacle_movement()
  │
  ├─→ find_closest_obstacle()
  │
  └─→ generate_evasion_trajectory()
        │
        ├─→ get_initial_path_from_global()
        │     └─→ global_wpnts_scaled_ 사용
        │
        ├─→ convert_obstacle_to_points()
        │
        └─→ TEB::optimize()
              │
              └─→ update_poses() (50번 반복)
                    │
                    ├─→ contraction_force()
                    ├─→ repulsive_force()
                    │     └─→ compute_rho()
                    ├─→ velocity_constraint_force()
                    │     └─→ compute_velocity()
                    ├─→ acceleration_constraint_force()
                    │     └─→ compute_acceleration()
                    ├─→ nonholonomic_constraint_force()
                    │     └─→ compute_nonholonomic_violation()
                    ├─→ turning_radius_constraint_force()
                    │     └─→ compute_turning_radius()
                    ├─→ optimize_time_interval()
                    └─→ update_orientation()
```

---

## 🎯 핵심 개념 정리

### Elastic Bands → TEB 확장

| 항목 | Elastic Bands | TEB |
|------|--------------|-----|
| **포즈** | 위치 + 반경 | 위치 + 방향 + 시간 + 반경 |
| **힘** | 수축력 + 반발력 | + 속도/가속도/비홀로노믹/회전반경 제약 |
| **목표** | 경로 최적화 | 경로 + 시간 최적화 |
| **제약** | 장애물 회피 | + 차량 동역학 제약 |

### 최적화 목표

**Equation (9):**
```
V(B) = Σ (f_v + f_a + f_obs + f_path + f_t + f_nh + f_r)
```

- `f_v`: 속도 제약
- `f_a`: 가속도 제약
- `f_obs`: 장애물 회피 (반발력)
- `f_path`: 경로 길이 (수축력)
- `f_t`: 시간 최적화
- `f_nh`: 비홀로노믹 제약
- `f_r`: 최소 회전 반경 제약

---

## 🚀 사용 방법

### 1. 빌드
```bash
cd ~/forza_ws/race_stack
colcon build --packages-select teb_local_planner --symlink-install
source install/setup.bash
```

### 2. 실행
```bash
ros2 launch teb_local_planner local_planner.launch.py
```

### 3. 확인
```bash
# 생성된 경로 확인
ros2 topic echo /planner/avoidance/otwpnts

# 시각화 마커 확인
ros2 topic echo /planner/avoidance/markers
```

---

## 📝 TODO 및 개선 사항

1. **Frenet 변환:** 현재는 간단한 근사 사용, 실제 FrenetConverter 사용 필요
2. **파라미터 튜닝:** 가중치들(kv, ka, knh 등)을 파라미터로 외부화
3. **최적화 알고리즘:** 현재는 gradient descent 방식, 더 고급 최적화 알고리즘 적용 가능
4. **장애물 예측:** 더 정교한 장애물 움직임 예측 모델 추가

---

## 🔍 디버깅 팁

1. **경로가 생성되지 않음:**
   - `get_initial_path_from_global()`에서 경로가 비어있는지 확인
   - 전역 경로 메시지가 도착했는지 확인

2. **장애물 회피가 안됨:**
   - `compute_rho()` 함수가 올바른 거리를 반환하는지 확인
   - `repulsive_force()`의 가중치(kr_repulsive_) 조정

3. **속도가 너무 느림:**
   - `optimize_time_interval()`에서 계산된 시간 간격 확인
   - `v_max` 파라미터 확인

---

이제 TEB 알고리즘이 완전히 통합되었습니다! 🎉

