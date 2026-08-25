# Knight-in-Love 

[![My Skills](https://skillicons.dev/icons?i=cpp,ros)](https://skillicons.dev)

This is an experimental repository for generating a **workspace envelope** for a robotic arm using **ROS 2**.

The model used is a **URDF 5-DOF robotic arm**.

## **RUNNING THE VISUALIZER**
To generate a workspace envelope of a robotic arm in **RViZ2**  with kinematic constraints applied to the joints.

**Initial setup involves** : 
- An RViZ instance for visualizing the URDF model.
- A second RViZ instance which displays the workspace-envelope of the robotic arm.
- A C++ node publishing joint-states to control the arm.
- Closing the Joint State Publisher GUI window after launching the node.
- Add a marker display through the GUI.
- Set topic to `/eef_tracker`. 
- The end effector tracker is comprised of two geometries:

    - point : a sphere corresponding to the end effector.
    - trail : a collection of points which shows a trail traversed by the end effector.

- color configuration of the trail and the point can be set by altering the (R,G,B,A) values in the `visualizer_node.cpp`.

---

## **TERMINAL COMMANDS**
```
ros2 launch ur_description view_ur.launch.py ur_type:=ur5e
ros2 run workspace_visualizer workspace_visualizer
```

## DEVELOPMENT STATUS : 
- Accuracy of generated trajectory is not accurate.
- The version of this project as of `/2026-08-25` has only proved the appearance of a trail and the spherical point in the visualizer.
- Further changes aim to involve more accurate workspace-envelope generation along with some fun features that are purely cosmetic but very cool to look at along with better structured documentation and explanation of the C++ code. 
