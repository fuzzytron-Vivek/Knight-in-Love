# Knight-in-Love 

[![My Skills](https://skillicons.dev/icons?i=cpp,ros)](https://skillicons.dev)

This is an experimental repository for generating a **workspace envelope** for a robotic arm using **ROS 2**.

The model used is a **URDF 5-DOF robotic arm**.

## **RUNNING THE VISUALIZER**
This experiment generates a workspace envelope of a robotic arm in **RViZ2** around the robotic arm with the given constraints/input parameters.

**Initial setup involves** : 
- An RViZ instance for visualizing the URDF model.
- A second RViZ instance which displays the workspace-envelope of the robotic arm.(WORK IN PROGRESS)
- A C++ node ,publishing joint-states to control the arm.

---

## **TERMINAL COMMANDS**
```
ros2 launch ur_description view_ur.launch.py ur_type:=ur5e
ros2 run workspace_visualizer workspace_visualizer
```
