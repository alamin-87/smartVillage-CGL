#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window dimensions
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;

// World coordinate mapping (virtual 1000x1000 grid for algorithms)
const float COORD_SCALE = 500.0f;

// Time & Animation
const float TARGET_FPS = 60.0f;
const float FRAME_TIME_MS = 1000.0f / TARGET_FPS;
const float DAY_CYCLE_SPEED = 0.2f;
const float NIGHT_THRESHOLD = 180.0f;
const float DAY_LENGTH = 360.0f;

// Scene offsets in world space
const float SCENE1_X = 0.0f;   // Village
const float SCENE2_X = 2.0f;   // Rural
const float SCENE3_X = 4.0f;   // Urban

// Camera
const float CAMERA_SMOOTHING = 0.05f;

// Weather
const int RAIN_DROP_COUNT = 100;
const float RAIN_DROP_MIN_SPEED = 0.05f;
const float RAIN_DROP_MAX_SPEED = 0.10f;
const float WIND_CLOUD_MULTIPLIER = 5.0f;
const float STORM_CLOUD_MULTIPLIER = 15.0f;
const int STORM_FLASH_DURATION = 10;

// Energy System
const float BASE_GRID_LOAD_KWH = 120.0f;
const float STREETLIGHT_POWER_KW = 0.15f;
const float HOUSE_POWER_KW = 0.8f;
const float BUILDING_POWER_KW = 2.5f;
const float SOLAR_PEAK_OUTPUT_KW = 5.0f;

// Smart Building
const float COMFORT_TEMP_MIN = 22.0f;
const float COMFORT_TEMP_MAX = 26.0f;
const float DAY_AMBIENT_TEMP = 32.0f;
const float NIGHT_AMBIENT_TEMP = 24.0f;

// Traffic
const float TRAFFIC_RED_DURATION = 300.0f;
const float TRAFFIC_GREEN_DURATION = 250.0f;
const float TRAFFIC_YELLOW_DURATION = 50.0f;

// Colors (commonly reused)
namespace Colors {
    const float SKY_DAY[] = {0.4f, 0.6f, 0.8f};
    const float SKY_NIGHT[] = {0.05f, 0.05f, 0.15f};
    const float GRASS[] = {0.2f, 0.8f, 0.2f};
    const float GRASS_NIGHT[] = {0.1f, 0.3f, 0.1f};
    const float WATER[] = {0.0f, 0.6f, 1.0f};
    const float WATER_NIGHT[] = {0.0f, 0.1f, 0.4f};
    const float ROAD[] = {0.2f, 0.2f, 0.2f};
    const float SKIN_TONE[] = {0.85f, 0.65f, 0.45f};
}

#endif
