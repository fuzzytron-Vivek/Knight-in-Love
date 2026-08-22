# Knight-in-Love 

[![My Skills](https://skillicons.dev/icons?i=cpp,ros)](https://skillicons.dev)

This is an experimental repository for generating a **workspace envelope** for a robotic arm using **ROS 2**.

The initial setup uses a **URDF 6DOF robotic arm** , further additions may involve custom models.

## **RUNNING THE VISUALIZER**
This experiment generates a workspace envelope of a robotic arm in RViZ-2. 
The goal is to generate a hollow envelope around the robotic arm with the given constraints/input parameters.

Initial setup involves : 
- An RViZ instance for visualizing the URDF model.

- A second RViZ instance which displays the workspace-envelope of the robotic arm.(WORK IN PROGRESS)

- A C++ node ,publishing joint-states to control the arm.
