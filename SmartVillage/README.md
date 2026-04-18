# 🏡 SmartVillage: Computer Graphics Laboratory Project

![Project Banner](https://img.shields.io/badge/CGL-Project-EB4034?style=for-the-badge&logo=opengl&logoColor=white)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

Welcome to **SmartVillage**, a state-of-the-art 2D Computer Graphics simulation built for the 8th Semester Computer Graphics Laboratory (CGL). This project demonstrates the intersection of traditional rasterization algorithms with modern object-oriented engine architecture to create a living, breathing digital environment.

---

## 🌟 Key Features

### 🔊 Dynamic Atmospheric Sound System
Integrated with the **Windows Media Control Interface (MCI)**, SmartVillage features a weather-responsive audio engine:
- 👋 **Real-time Weather Audio**: Ambient rain, storm, and wind sound loops that sync with visual effects.
- 🚶 **Interactive Child Sound**: Manual toggle control over child vocalizations (Press 'C').
- 🐄 **Life-like Entity Sounds**: Sounds for cows, goats, and hens with optimized clucking frequency.

### 🚶 Advanced Entity Animation
- **4-Directional Movement**: Humans and children features realistic 4-oriented walking (Front, Back, Side) with unique rendering for each view.
- **Stable Navigation**: Adjusted movement speeds for a natural, grounded feel.
- **Enhanced Wildlife**: Redesigned birds with segmented wings and fan tails for lifelike flight.

### 🌤️ Environment & Weather Engine
- **Day/Night Cycle**: A smooth 360-degree solar orbit that transitions the world between dawn, midday, twilight, and deep night.
- **Dynamic Skybox**: Color-shifting gradients reflecting atmospheric scattering.
- **Particle Systems**: Custom weather effects including rain, storms, and wind-driven cloud movements.
- **Natural Lighting**: Hand-calculated shadows and ambient shifts based on sun/moon position.

### 🔋 Smart Logic Systems
- **Energy Grid Tracking**: A real-time monitoring system calculating solar generation vs. community power load.
- **Automated Lighting**: Solar-sensing streetlights that activate automatically at dusk.
- **Smart Infrastructure**: Functional hospital emergency lighting, educational center state tracking, and building HVAC simulations.

---

## 🗺️ Scene Overviews

SmartVillage features three distinct, strictly decoupled environments:

1. **Main Village (1)**: The heart of the simulation featuring a bustling market, a detailed child park (with animated swings, slides, and merry-go-rounds), and a flowing river with dynamic ripples and aquatic life.
2. **Rural Homestead (2)**: A serene landscape focusing on agriculture, featuring crop-rotation farmlands, traditional mud houses, and livestock management.
3. **Urban District (3)**: A modern smart-city expansion with high-rise buildings, automated traffic control systems, hospitals, and educational institutions.

---

## 🕹️ Controls

| Key | Action |
| :--- | :--- |
| **`1`** | Switch to **Main Village** |
| **`2`** | Switch to **Rural Homestead** |
| **`3`** | Switch to **Urban District** |
| **`C`** | Toggle **Child Sound** (On/Off Loop) |
| **`D` / `N`** | Force **Day** / **Night** Mode |
| **`R` / `S` / `W`** | Toggle **Rain** / **Storm** / **Wind** |
| **`ESC`** | Exit Simulation |

---

## 🏗️ Technical Architecture

The project follows a modular, engine-like directory structure:

- **`algorithms/`**: 🧪 Foundation layer implementing **Bresenham's**, **DDA**, and **Midpoint Circle** from scratch.
- **`app/`**: 🎮 Application state and high-level scene management.
- **`core/`**: ⚙️ Rendering hooks, input processing, and delta-time management.
- **`entities/`**: 🚶 Living components (Humans, Animals, Fish) with independent AI states.
- **`systems/`**: 🛠️ Global logic handlers (Day/Night, Weather, SoundManager).
- **`smart/`**: 💡 Logic dedicated to the "Smart" ecosystem (EnergyGrid, Automated Lighting).
- **`objects/`**: 🏘️ Static environment pieces (Houses, Bridges, Roads, Markets).

---

## 🚀 Getting Started

### Prerequisites
- **Compiler**: GCC / MinGW (supporting C++17 or higher)
- **Dependencies**: freeglut, OpenGL, WinMM (for audio)

### Building & Running
The project includes a PowerShell build script that handles recursive compilation and library linking:

1. Open PowerShell in the project directory.
2. Run the build script:
   ```powershell
   .\build_and_run.ps1
   ```

---

## 📂 File Structure
```text
SmartVillage/
├── algorithms/      # Core rasterization implementations
├── app/             # Application lifecycle
├── assets/          # Sprites and textures
├── config/          # Project constants and defines
├── entities/        # Interactive NPCs and animals
├── media/           # Sound files (.mp3)
├── objects/         # Static environment assets
├── scene/           # Scene-specific logic
├── systems/         # Global managers (Sound, Time, Weather)
└── main.cpp         # Entry point
```

---
*Developed for the 8th Semester Computer Graphics Laboratory.*
