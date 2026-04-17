#include "daynight_system.h"
#include <cmath>

DayNightSystem::DayNightSystem() {
    sunAngle = 45.0f;
    night = false;
    cycleSpeed = 0.2f;
}

DayNightSystem& DayNightSystem::getInstance() {
    static DayNightSystem instance;
    return instance;
}

void DayNightSystem::update(float dt) {
    sunAngle += cycleSpeed;
    if (sunAngle > 360.0f) sunAngle -= 360.0f;
    night = (sunAngle > 180.0f);
}

void DayNightSystem::forceDay() { sunAngle = 45.0f; night = false; }
void DayNightSystem::forceNight() { sunAngle = 200.0f; night = true; }

bool DayNightSystem::isDusk() const {
    return (sunAngle > 160.0f && sunAngle < 200.0f);
}

bool DayNightSystem::isDawn() const {
    return (sunAngle > 340.0f || sunAngle < 20.0f);
}

int DayNightSystem::getHour() const {
    return ((int)(sunAngle / 15.0f) + 6) % 24;
}

float DayNightSystem::getDayProgress() const {
    return sunAngle / 360.0f;
}

void DayNightSystem::getSkyColor(float& r, float& g, float& b) const {
    float intensity = sin(sunAngle * 3.14159f / 180.0f);
    if (intensity > 0) {
        // Daytime: blue sky
        r = 0.4f + (0.1f * (1.0f - intensity));
        g = 0.6f + (0.2f * intensity);
        b = 0.8f + (0.2f * intensity);
    } else {
        // Nighttime: dark blue
        float nightFactor = -intensity;
        r = 0.05f * (1.0f - nightFactor);
        g = 0.05f * (1.0f - nightFactor);
        b = 0.15f + (0.05f * (1.0f - nightFactor));
    }
}

float DayNightSystem::getAmbientIntensity() const {
    float intensity = sin(sunAngle * 3.14159f / 180.0f);
    if (intensity < 0) return 0.15f; // Minimum night light
    return 0.15f + 0.85f * intensity;
}
