# 2D Particle Simulator

A real-time 2D particle physics simulator built in C++ using OpenGL and GLFW.

## Demo

<p align="center">
  <b>50 Circles</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <b>100 Circles</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <b>800 Circles</b>
</p>

<p align="center">
  <img src="demo/demo-50.gif" width="31%" />
  <img src="demo/demo-100.gif" width="31%" />
  <img src="demo/demo-800.gif" width="31%" />
</p>


## Features

- Simulates many moving particles in real time
- Particle-to-particle collision detection
- Wall collision detection
- Collision response using vector mathematics
- Delta-time-based movement
- GPU rendering with OpenGL shaders

## Technologies

- C++
- OpenGL
- GLFW
- GLSL

## How It Works

Each particle has a position and velocity that are updated every frame.

The program checks particles for collisions and calculates updated velocities when collisions occur. The resulting particle positions are then rendered using OpenGL.

## What I Learned

This project gave me experience with:

- Real-time graphics programming
- Collision detection and response
- Vector mathematics
- OpenGL rendering
- Shader programming
- C++ project organization
