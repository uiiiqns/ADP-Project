# TEB Local Planner 결과 확인 가이드

## 📊 결과 확인 방법

### 1. 토픽 리스트 확인
현재 발행되고 있는 모든 토픽을 확인합니다:

```bash
ros2 topic list
```

특히 다음 토픽들이 보여야 합니다:
- `/planner/avoidance/markers` - 시각화 마커
- `/planner/avoidance/otwpnts` - 생성된 경로 waypoints
- `/planner/avoidance/considered_OBS` - 고려된 장애물
- `/planner/avoidance/propagated_obs` - 예측된 장애물
- `/planner/avoidance/latency` - 처리 시간 (measure=true일 때)

### 2. 토픽 정보 확인
각 토픽의 타입과 발행 빈도를 확인합니다:

```bash
# 경로 waypoints 정보
ros2 topic info /planner/avoidance/otwpnts

# 시각화 마커 정보
ros2 topic info /planner/avoidance/markers

# 발행 빈도 확인 (Hz)
ros2 topic hz /planner/avoidance/otwpnts
ros2 topic hz /planner/avoidance/markers
```

### 3. 메시지 내용 확인 (Echo)

#### 생성된 경로 확인
```bash
ros2 topic echo /planner/avoidance/otwpnts
```

출력 예시:
- `wpnts[]`: 생성된 waypoint 배열
  - `id`: waypoint ID
  - `x_m`, `y_m`: 위치 좌표
  - `s_m`, `d_m`: Frenet 좌표
  - `vx_mps`: 속도

#### 시각화 마커 확인
```bash
ros2 topic echo /planner/avoidance/markers
```

#### 처리 시간 확인 (measure=true일 때)
```bash
ros2 topic echo /planner/avoidance/latency
```

### 4. RViz로 시각화 (권장)

RViz를 사용하면 경로와 장애물을 시각적으로 확인할 수 있습니다:

```bash
# 새 터미널에서
rviz2
```

RViz에서 설정:
1. **Fixed Frame**: `map` 설정
2. **Add** → **By topic** → `/planner/avoidance/markers` 선택
   - MarkerArray 타입으로 경로가 시각화됩니다
3. **Add** → **By topic** → `/planner/avoidance/considered_OBS` 선택
   - 고려된 장애물이 표시됩니다

### 5. 입력 토픽 확인

플래너가 제대로 동작하려면 다음 입력 토픽들이 발행되고 있어야 합니다:

```bash
# 장애물 정보 확인
ros2 topic echo /perception/obstacles

# 차량 상태 확인
ros2 topic echo /car_state/frenet/odom

# 전역 경로 확인
ros2 topic echo /global_waypoints
ros2 topic echo /global_waypoints_scaled
```

### 6. 토픽 발행 상태 확인

```bash
# 모든 토픽의 발행 빈도 확인
ros2 topic hz /planner/avoidance/otwpnts
ros2 topic hz /planner/avoidance/markers

# 토픽이 발행되고 있는지 확인
ros2 topic list | grep planner
```

## 🔍 디버깅 팁

### 경로가 생성되지 않는 경우

1. **입력 데이터 확인:**
   ```bash
   # 장애물이 있는지 확인
   ros2 topic echo /perception/obstacles --once
   
   # 전역 경로가 있는지 확인
   ros2 topic echo /global_waypoints_scaled --once
   ```

2. **필터링 조건 확인:**
   - `obs_traj_tresh`: 장애물의 d_center가 이 값보다 작아야 함
   - `lookahead`: 장애물이 이 거리 안에 있어야 함

3. **로그 확인:**
   - 노드 실행 터미널에서 에러 메시지 확인
   - "All required messages received" 메시지가 나왔는지 확인

### 경로는 생성되지만 이상한 경우

1. **Waypoint 개수 확인:**
   ```bash
   ros2 topic echo /planner/avoidance/otwpnts --once | grep -A 5 "wpnts:"
   ```

2. **속도 값 확인:**
   ```bash
   ros2 topic echo /planner/avoidance/otwpnts --once | grep "vx_mps"
   ```

3. **마커 확인:**
   - RViz에서 마커가 제대로 표시되는지 확인
   - 마커 색상과 크기가 속도를 나타냄

## 📈 성능 확인

### 처리 시간 측정
`config/local_planner.yaml`에서 `measure: true`로 설정하면:

```bash
ros2 topic echo /planner/avoidance/latency
```

처리 시간(ms)이 출력됩니다. 20Hz 실행이므로 50ms 이하가 이상적입니다.

## 🎯 빠른 확인 스크립트

다음 스크립트로 한 번에 확인할 수 있습니다:

```bash
#!/bin/bash
echo "=== 토픽 리스트 ==="
ros2 topic list | grep planner

echo -e "\n=== 경로 waypoints (최근 1개) ==="
ros2 topic echo /planner/avoidance/otwpnts --once | head -20

echo -e "\n=== 발행 빈도 ==="
timeout 3 ros2 topic hz /planner/avoidance/otwpnts 2>/dev/null || echo "토픽이 발행되지 않음"
```

## 💡 다음 단계

1. **RViz로 시각화**: 가장 직관적인 확인 방법
2. **토픽 echo**: 데이터 내용 확인
3. **성능 측정**: latency 토픽으로 처리 시간 확인
4. **파라미터 튜닝**: 결과에 따라 config 파일 수정


