# 🏡 SmartVillage: Computer Graphics Laboratory Project

Welcome to the **SmartVillage** repository! This is a comprehensive 2D/3D graphics application built from scratch in C++ for the 8th Semester Computer Graphics Laboratory (CGL). 

The goal of this project is to simulate a dynamic, living smart village by integrating core graphics implementations with custom logic systems (such as environment and dynamic movements).

## 🌟 Project Overview

**SmartVillage** isn't just static objects painted on a screen; it's a living environment. The project aims to implement advanced and interactive rendering features—animated weather, day/night cycles, ambient lighting, and smart energy tracking. 

Crucially, **to meet the academic requirements of the CGL course**, this project implements foundational rasterization algorithms (like DDA and Bresenham's) from scratch in order to construct the scenes.

## ✨ Key Features
- **Dynamic Weather System:** Real-time simulations of rain, storm, and wind effects acting upon the environment.
- **Day/Night Cycle:** Smooth color shifting and ambient transitions between daytime, twilight, and night.
- **Smart Infrastructure:** Automated lighting grids and building energy analysis representing a modern "Smart" ecosystem.
- **Living Entities:** Independent logic for moving humans, children, and animals updating in real-time.
- **HUD Interface:** Real-time on-screen data displaying smart stats, FPS, and simulation variables.

## 📂 Architecture and Directory Structure

The project has been scaled with an organized, engine-like architecture:

- **`app/`**: High-level application loops and scene management logic.
- **`core/`**: The core application foundation including rendering hooks, input processing, and delta-time management.
- **`scene/`**: The composite layer that groups objects and interactive entities into the main village setting.
- **`objects/`**: Implements static drawable environment pieces (Houses, Trees, Rivers, Roads, Bridges).
- **`entities/`**: Represents moving, interactive components (Humans, Children, Animals).
- **`systems/`**: **🔥 The Logic Engine.** Handlers acting upon the world states (Animation, Weather, DayNight, Movement).
- **`smart/`**: Code dedicated to the "Smart" logic. Manages grid automation, lighting systems, and energy consumption.
- **`effects/`**: Visual overlays applied on the finalized scenes (like particle-based weather).
- **`ui/`**: Specialized on-screen overlays and Heads-Up Displays (HUD).
- **`math/`**: Mathematical functions (Transforms, Interpolations).
- **`algorithms/`**: **📚 Academic implementations.** Direct translation of primitive rasterization algorithms handling the actual pixel-drawing.
- **`config/`**: Global macros, engine constants, and screen configurations.
- **`assets/`**: Repository for local textures and sound data.

## 📚 Academic Code (CGL Algorithms)
This section forms the core requirement for the course grading. The `algorithms/` module encapsulates fundamental line-drawing and primitive rasterization math:
1. **DDA (Digital Differential Analyzer) Algorithm** (`dda.cpp / .h`)
2. **Bresenham's Line Algorithm** (`bresenham.cpp / .h`)
3. **Midpoint Circle Drawing Algorithm** (`midpoint_circle.cpp / .h`)

By routing calls from the `core/renderer` and static `objects/` through these mathematical constructs, the project visually demonstrates the underlying mechanics of computer graphics.

## 🚀 Getting Started

### Prerequisites
- C++ Compiler (GCC / MinGW / MSVC)
- Graphics Library (e.g., OpenGL/GLUT, SDL2, or SFML)

### Building
*(Add your environment-specific build or Makefile instructions here)*

### Controls
*(Add runtime controls handled by your input_manager here once finalized)*

---
*Developed for 8th Semester CGL.*
