# ADP-Project

## ForzaETH Local Planner Package

This repository currently hosts a ROS 2 Humble skeleton package named `teb_local_planner`.  
The package does not contain planning logic yet; it only wires the basic node, topics, launch file, and configuration placeholders so algorithm development can start quickly.

### Layout

- `teb_local_planner/package.xml` – package metadata and dependencies
- `teb_local_planner/CMakeLists.txt` – build instructions with component + executable targets
- `teb_local_planner/include/` – node interface (`LocalPlannerNode`)
- `teb_local_planner/src/` – node implementation and main entry point
- `teb_local_planner/config/` – default parameters (`local_planner.yaml`)
- `teb_local_planner/launch/` – example launch file binding the config
- `teb_local_planner/test/` – starter GTest proving node initialization

### Build Instructions

```bash
cd /home/subin/Desktop/subin/ADP-Project/ADP-Project
colcon build --packages-select teb_local_planner
source install/setup.bash
```

### Run the Node

```bash
ros2 launch teb_local_planner local_planner.launch.py
```

### Next Steps

- Replace placeholder subscriptions/publishers with actual message types in your stack
- Implement the planning loop inside `LocalPlannerNode::on_timer`
- Extend `config/local_planner.yaml` with the hyper-parameters you require
