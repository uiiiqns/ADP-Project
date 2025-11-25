# PPT용 핵심 코드 정리

## 📋 1. 전체 아키텍처

### 파일 구조
```
teb_local_planner/
├── include/teb_local_planner/
│   ├── local_planner_node.hpp  # ROS2 노드 인터페이스
│   └── teb.hpp                 # TEB 알고리즘 클래스
└── src/
    ├── local_planner_node.cpp  # 노드 구현
    └── teb.cpp                 # TEB 알고리즘 구현
```

---

## 🔄 2. 메인 루프 (핵심 흐름)

### `LocalPlannerNode::on_timer()` - 메인 플래닝 루프

```cpp
void LocalPlannerNode::on_timer()
{
  // 1. 메시지 대기
  if (!messages_ready_) {
    messages_ready_ = check_messages_ready();
    if (!messages_ready_) return;
  }

  // 2. 장애물 필터링
  std::vector<f110_msgs::msg::Obstacle> close_obstacles = filter_obstacles();

  // 3. 가장 가까운 장애물 선택
  if (!close_obstacles.empty()) {
    auto closest_obs = find_closest_obstacle(close_obstacles);
    
    // 4. TEB로 회피 경로 생성
    std::tie(wpnts, markers) = generate_evasion_trajectory(closest_obs);
  }

  // 5. 결과 발행
  otwpnts_pub_->publish(wpnts);
  markers_pub_->publish(markers);
}
```

**핵심 포인트:**
- 20Hz로 주기적 실행
- 장애물 필터링 → TEB 최적화 → 경로 발행

---

## 🎯 3. TEB 핵심 클래스

### `TEBPose` 구조체 - Elastic Bands Bubble 확장

```cpp
struct TEBPose {
  Eigen::Vector2d pos;    // 위치 [x, y]
  double theta;            // 방향 β (rad)
  double delta_t;          // 시간 간격 ΔT (sec)
  double radius;           // 안전 반경 (장애물까지 거리)
};
```

**비교:**
- **Elastic Bands:** 위치 + 반경만
- **TEB:** 위치 + 방향 + 시간 + 반경

---

## ⚡ 4. TEB 최적화 과정

### `TEB::optimize()` - 최적화 반복

```cpp
void TEB::optimize(int max_iter = 50)
{
  for (int iter = 0; iter < max_iter; iter++) {
    update_poses();  // 각 포즈 업데이트
  }
}
```

### `TEB::update_poses()` - 포즈 업데이트 (핵심)

```cpp
void TEB::update_poses()
{
  for (size_t i = 0; i < poses_.size(); i++) {
    // 1. 모든 힘 합산
    Eigen::Vector2d f_total = 
      contraction_force(i) +           // 경로 단축
      repulsive_force(i) +              // 장애물 회피
      velocity_constraint_force(i) +    // 속도 제약
      acceleration_constraint_force(i) + // 가속도 제약
      nonholonomic_constraint_force(i) + // 비홀로노믹 제약
      turning_radius_constraint_force(i); // 회전 반경 제약
    
    // 2. 접선 방향 제거
    f_star = f_total - (f_total · v) * v / ||v||²
    
    // 3. 적응형 스텝으로 위치 업데이트
    new_pos = pos[i] + radius[i] * f_star
    
    // 4. 시간 간격 최적화
    new_dt = optimize_time_interval(i)
    
    // 5. 방향 업데이트
    update_orientation(i)
  }
}
```

---

## 🔧 5. 핵심 힘 계산 함수들

### 5-1. `contraction_force()` - 수축력 (Elastic Bands 기본)

```cpp
Eigen::Vector2d TEB::contraction_force(int i) const
{
  const auto& prev = poses_[i - 1].pos;
  const auto& next = poses_[i + 1].pos;
  const auto& current = poses_[i].pos;
  
  Eigen::Vector2d dir_prev = (prev - current).normalized();
  Eigen::Vector2d dir_next = (next - current).normalized();
  
  return kc_ * (dir_prev + dir_next);
}
```

**의미:** 인접 포즈들이 현재 포즈를 당겨 경로를 짧게 만듦

---

### 5-2. `repulsive_force()` - 반발력 (Elastic Bands 기본)

```cpp
Eigen::Vector2d TEB::repulsive_force(int i) const
{
  const auto& b = poses_[i].pos;
  double rho = poses_[i].radius;  // 장애물까지 거리
  
  if (rho >= rho0_) return Eigen::Vector2d::Zero();
  
  // 그래디언트 근사 (finite difference)
  double h = step_size_;
  double grad_x = (compute_rho(b - dx) - compute_rho(b + dx)) / (2.0 * h);
  double grad_y = (compute_rho(b - dy) - compute_rho(b + dy)) / (2.0 * h);
  Eigen::Vector2d grad(grad_x, grad_y);
  
  return kr_repulsive_ * (rho0_ - rho) * grad;
}
```

**의미:** 장애물로부터 멀어지게 하는 힘

---

### 5-3. `velocity_constraint_force()` - 속도 제약 (TEB 추가)

```cpp
Eigen::Vector2d TEB::velocity_constraint_force(int i) const
{
  double v = compute_velocity(i);  // v = ||pos[i+1] - pos[i]|| / ΔT
  
  if (v > v_max_) {
    Eigen::Vector2d dir = (poses_[i + 1].pos - poses_[i].pos).normalized();
    return -kv_ * (v - v_max_) * dir;
  }
  
  return Eigen::Vector2d::Zero();
}
```

**의미:** 최대 속도를 초과하지 않도록 제어

---

### 5-4. `compute_turning_radius()` - 회전 반경 계산 (Equation 8)

```cpp
double TEB::compute_turning_radius(int i) const
{
  // Equation (8): ρ_k = ||d_k||_2 / (2 * sin(Δβ_k / 2))
  Eigen::Vector2d d = poses_[i + 1].pos - poses_[i].pos;
  double delta_beta = poses_[i + 1].theta - poses_[i].theta;
  
  double d_norm = d.norm();
  double sin_half = std::sin(std::abs(delta_beta) / 2.0);
  
  return d_norm / (2.0 * sin_half);
}
```

**수식:**
```
ρ_k = ||d_k||_2 / (2 * sin(Δβ_k / 2))
```

---

### 5-5. `turning_radius_constraint_force()` - 최소 회전 반경 제약

```cpp
Eigen::Vector2d TEB::turning_radius_constraint_force(int i) const
{
  double rho = compute_turning_radius(i);
  
  if (rho < rho_min_) {
    Eigen::Vector2d dir = (poses_[i + 1].pos - poses_[i].pos).normalized();
    return -kr_radius_ * (rho_min_ - rho) * dir;
  }
  
  return Eigen::Vector2d::Zero();
}
```

**의미:** 최소 회전 반경보다 작게 회전하지 않도록 제어

---

### 5-6. `compute_nonholonomic_violation()` - 비홀로노믹 제약 (Equation 7)

```cpp
double TEB::compute_nonholonomic_violation(int i) const
{
  // Equation (7): h_k = (dir_i + dir_i1) · d_k ≈ 0
  Eigen::Vector2d d = poses_[i + 1].pos - poses_[i].pos;
  Eigen::Vector2d dir_i(std::cos(poses_[i].theta), std::sin(poses_[i].theta));
  Eigen::Vector2d dir_i1(std::cos(poses_[i + 1].theta), std::sin(poses_[i + 1].theta));
  
  Eigen::Vector2d sum_dir = dir_i + dir_i1;
  double violation = std::abs(sum_dir.dot(d));
  
  return violation;
}
```

**수식:**
```
h_k = (dir_i + dir_i1) · d_k = 0
```

**의미:** 연속된 두 포즈가 같은 곡률의 호 위에 있어야 함

---

### 5-7. `optimize_time_interval()` - 시간 최적화

```cpp
double TEB::optimize_time_interval(int i) const
{
  // 시간 최적화: 속도 제약을 만족하는 최소 시간
  double dist = (poses_[i + 1].pos - poses_[i].pos).norm();
  double optimal_dt = dist / v_max_;
  
  return std::max(MIN_DT, optimal_dt);
}
```

**목표:** Equation (2) - `min Σ ΔT_k²`

---

## 📊 6. 전체 목적 함수 (Equation 9)

### 수식 표현

```
V(B) = Σ_{k=1}^{n-1} (f_v + f_a + f_obs + f_path + f_t + f_nh + f_r)
```

**구성 요소:**
- `f_v`: 속도 제약 (`velocity_constraint_force`)
- `f_a`: 가속도 제약 (`acceleration_constraint_force`)
- `f_obs`: 장애물 회피 (`repulsive_force`)
- `f_path`: 경로 길이 (`contraction_force`)
- `f_t`: 시간 최적화 (`time_optimization_cost`)
- `f_nh`: 비홀로노믹 제약 (`nonholonomic_constraint_force`)
- `f_r`: 최소 회전 반경 제약 (`turning_radius_constraint_force`)

---

## 🔗 7. 함수 호출 흐름도

```
on_timer() (20Hz)
  │
  ├─→ filter_obstacles()
  │     └─→ predict_obstacle_movement()
  │
  ├─→ find_closest_obstacle()
  │
  └─→ generate_evasion_trajectory()
        │
        ├─→ get_initial_path_from_global()
        ├─→ convert_obstacle_to_points()
        │
        └─→ TEB::optimize(50)
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

## 📈 8. Elastic Bands → TEB 확장 비교

| 항목 | Elastic Bands | TEB |
|------|--------------|-----|
| **포즈** | 위치 + 반경 | 위치 + 방향 + 시간 + 반경 |
| **힘 종류** | 2개 (수축, 반발) | 6개 (+ 속도/가속도/비홀로노믹/회전반경) |
| **목표** | 경로 최적화 | 경로 + 시간 최적화 |
| **제약** | 장애물 회피 | + 차량 동역학 제약 |

---

## 🎯 9. 핵심 수식 정리

### Equation (2) - 시간 최적화 목표
```
min_B Σ_{k=1}^{n-1} ΔT_k²
```

### Equation (7) - 비홀로노믹 제약
```
h_k = (dir_i + dir_i1) · d_k = 0
```

### Equation (8) - 회전 반경 계산
```
ρ_k = ||d_k||_2 / (2 * sin(Δβ_k / 2))
```

### Equation (9) - 전체 목적 함수
```
V(B) = Σ_{k=1}^{n-1} (f_v + f_a + f_obs + f_path + f_t + f_nh + f_r)
```

---

## 💡 10. PPT 슬라이드 구성 제안

### 슬라이드 1: 개요
- Elastic Bands 기반 TEB 구현
- ROS2 Humble 환경
- C++ 구현

### 슬라이드 2: 전체 구조
- 파일 구조
- 클래스 다이어그램

### 슬라이드 3: 메인 루프
- `on_timer()` 함수 코드
- 실행 흐름도

### 슬라이드 4: TEB 최적화
- `update_poses()` 함수
- 6가지 힘 계산

### 슬라이드 5: 핵심 힘 함수들
- 수축력, 반발력 코드
- 속도/가속도 제약 코드

### 슬라이드 6: 수식 정리
- Equation (7), (8), (9)
- 각 수식의 의미

### 슬라이드 7: Elastic Bands → TEB 확장
- 비교 테이블
- 추가된 기능

### 슬라이드 8: 결과
- 토픽 인터페이스
- 성능 측정

---

이 내용을 PPT에 활용하세요! 🎯



