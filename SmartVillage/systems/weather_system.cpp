#include "weather_system.h"
#include <cmath>

WeatherSystem::WeatherSystem() {
    rainy = false; stormy = false; windy = false;
    windStrength = 0.0f;
    rainIntensity = 0.0f;
    temperature = 30.0f;
    transitionTimer = 0.0f;
}

WeatherSystem& WeatherSystem::getInstance() {
    static WeatherSystem instance;
    return instance;
}

void WeatherSystem::update(float dt) {
    transitionTimer += dt;

    // Smooth wind strength transitions
    float targetWind = windy ? 0.8f : (stormy ? 1.0f : 0.1f);
    windStrength += (targetWind - windStrength) * 0.02f;

    // Smooth rain intensity transitions
    float targetRain = stormy ? 1.0f : (rainy ? 0.6f : 0.0f);
    rainIntensity += (targetRain - rainIntensity) * 0.03f;

    // Temperature affected by weather
    float baseTemp = 30.0f;
    if (rainy) baseTemp -= 5.0f;
    if (stormy) baseTemp -= 10.0f;
    if (windy) baseTemp -= 2.0f;
    temperature += (baseTemp - temperature) * 0.01f;
}

void WeatherSystem::toggleRain() { rainy = !rainy; }
void WeatherSystem::toggleStorm() { 
    stormy = !stormy; 
    if (stormy) rainy = true; // Storm implies rain
}
void WeatherSystem::toggleWind() { windy = !windy; }

const char* WeatherSystem::getStatusText() const {
    if (stormy) return "STORM WARNING";
    if (rainy && windy) return "RAIN + WIND";
    if (rainy) return "RAINING";
    if (windy) return "WINDY";
    return "CLEAR SKY";
}
