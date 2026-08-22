# Knight-in-Love 

[![My Skills](https://skillicons.dev/icons?i=cpp,ros)](https://skillicons.dev)

This is a ROS2 based repository aimed at generating a **workspace envelope** for a robotic arm.

The initial setup uses a **URDF 6DOF robotic arm** , further additions may involve custom models.

## **RUNTIME INSTRUCTIONS**
This experiment involves generating a workspace envelope of a robotic arm in the RViZ2 simulator. 
The intent was to generate a hollow envelope around the robotic arm with the given constraints/input parameters.

Initial setup involves : 
- A terminal running the RViZ simulation responsible for visualizing the URDF model.

  [`ros2 launch ur_description view_ur.launch.py ur_type:=ur5e`]

- A terminal running the second RViZ window which shows a hollow cloud (workspace-envelope) of the robotic arm
  `in process`
  
- A terminal running the C++ node publishing joint-states to control the arm

  `ros2 run workspace_visualizer workspace_visualizer`
