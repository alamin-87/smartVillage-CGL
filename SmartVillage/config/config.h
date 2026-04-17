#ifndef CONFIG_H
#define CONFIG_H

// Feature toggles - enable/disable systems for debugging
#define ENABLE_WEATHER_SYSTEM   1
#define ENABLE_DAYNIGHT_CYCLE   1
#define ENABLE_SMART_GRID       1
#define ENABLE_HUD              1
#define ENABLE_ANIMATIONS       1
#define ENABLE_PARTICLES        1

// Debug options
#define DEBUG_SHOW_FPS          0
#define DEBUG_SHOW_COORDINATES  0

// Simulation speed multiplier (1.0 = normal, 2.0 = double speed)
const float SIM_SPEED = 1.0f;

#endif
