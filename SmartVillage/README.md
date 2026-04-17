# 🏡 SmartVillage: Computer Graphics Laboratory Project

Welcome to the **SmartVillage** repository! This is a comprehensive 2D/3D graphics application built from scratch in C++ for the 8th Semester Computer Graphics Laboratory (CGL). 

The goal of this project is to simulate a dynamic, living smart village by integrating core graphics implementations with custom logic systems (such as environment and dynamic movements).

## 🌟 Project Overview

**SmartVillage** isn't just static objects painted on a screen; it's a living environment. The project aims to implement advanced and interactive rendering features—animated weather, day/night cycles, ambient lighting, and smart energy tracking. 

Crucially, **to meet the academic requirements of the CGL course**, this project implements foundational rasterization algorithms (like DDA and Bresenham's) from scratch in order to construct the scenes.

## ✨ Key Features
- **Multi-Scene Support:** Switch between **Main Village**, **Rural Homestead**, and **Urban District**.
- **Dynamic Weather System:** Real-time simulations of rain, storm, and wind effects acting upon the environment.
- **Day/Night Cycle:** Smooth color shifting and ambient transitions between daytime, twilight, and night.
- **Smart Infrastructure:** Automated lighting grids and building energy analysis representing a modern "Smart" ecosystem.
- **Living Entities:** Independent logic for moving adults, children, and animals updating in real-time.
- **Premium HUD Interface:** Real-time on-screen data displaying smart stats, environment status, and simulation variables.

## 📂 Architecture and Directory Structure

The project has been scaled with an organized, engine-like architecture:

- **`app/`**: High-level application loops and scene management logic.
- **`core/`**: The core application foundation including rendering hooks, input processing, and delta-time management.
- **`scene/`**: Different simulation environments (Village, Rural, Urban).
- **`objects/`**: Implements static drawable environment pieces (Houses, Trees, Rivers, Roads, Bridges).
- **`entities/`**: Represents moving, interactive components (Humans, Children, Animals).
- **`systems/`**: Logic handlers acting upon the world states.
- **`smart/`**: Code dedicated to the "Smart" logic (Grid automation, Lighting).
- **`effects/`**: Visual overlays (Particle-based weather).
- **`ui/`**: Specialized on-screen overlays and HUD.
- **`algorithms/`**: **Academic implementations.** DDA, Bresenham, and Midpoint Circle algorithms.

## 🚀 Getting Started

### Prerequisites
- C++ Compiler (GCC / MinGW / MSVC)
- Graphics Library (FreeGLUT)

### Building & Running

1. Open PowerShell in the project directory.
2. Run the build script:
   ```powershell
   .\build_and_run.ps1
   ```

### 🕹️ Controls

- **1**: Switch to **Main Village Scene**
- **2**: Switch to **Rural Homestead Scene**
- **3**: Switch to **Urban District Scene**
- **D**: Force **Day Mode**
- **N**: Force **Night Mode**
- **R**: Toggle **Rain Mode**
- **S**: Toggle **Storm Mode**
- **W**: Toggle **Wind Mode**
- **ESC**: Exit Simulation

---
*Developed for 8th Semester CGL.*
