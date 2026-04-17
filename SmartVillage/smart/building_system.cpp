#include "building_system.h"
#include <cmath>
#include <cstdlib>

// --- SmartBuildingData ---
SmartBuildingData::SmartBuildingData() {
    temperature = 28.0f;
    energyUsage = 0.5f;
    occupants = 0;
    acOn = false;
    lightsOn = false;
    comfortScore = 75.0f;
}

void SmartBuildingData::update(float dt, bool isNight, float outsideTemp) {
    // Smart occupancy: more people during day (work/school hours)
    if (!isNight) {
        occupants = 5 + (rand() % 10);
    } else {
        occupants = 1 + (rand() % 3);
    }

    // Auto AC logic: turn on if temperature > 26
    if (temperature > 26.0f && occupants > 0) {
        acOn = true;
    } else if (temperature < 23.0f) {
        acOn = false;
    }

    // Auto lights: on at night if occupied
    lightsOn = (isNight && occupants > 0);

    // Temperature simulation
    float targetTemp = outsideTemp;
    if (acOn) targetTemp = 24.0f;
    temperature += (targetTemp - temperature) * 0.01f;

    // Energy calculation
    energyUsage = 0.2f; // base
    if (acOn) energyUsage += 1.5f;
    if (lightsOn) energyUsage += 0.3f;
    energyUsage += occupants * 0.05f; // per-person load

    // Comfort score (100 = perfect)
    comfortScore = 100.0f;
    if (temperature < 22.0f) comfortScore -= (22.0f - temperature) * 5.0f;
    if (temperature > 26.0f) comfortScore -= (temperature - 26.0f) * 5.0f;
    if (!lightsOn && isNight) comfortScore -= 15.0f;
    if (comfortScore < 0.0f) comfortScore = 0.0f;
}

// --- BuildingSystem ---
BuildingSystem::BuildingSystem() {
    buildingCount = 6; // Village houses + school + hospital + urban buildings
    for (int i = 0; i < buildingCount; i++) {
        buildings[i] = SmartBuildingData();
    }
}

BuildingSystem& BuildingSystem::getInstance() {
    static BuildingSystem instance;
    return instance;
}

void BuildingSystem::update(float dt, bool isNight, float outsideTemp) {
    for (int i = 0; i < buildingCount; i++) {
        buildings[i].update(dt, isNight, outsideTemp);
    }
}

int BuildingSystem::getTotalOccupants() const {
    int total = 0;
    for (int i = 0; i < buildingCount; i++) total += buildings[i].occupants;
    return total;
}

float BuildingSystem::getTotalEnergy() const {
    float total = 0.0f;
    for (int i = 0; i < buildingCount; i++) total += buildings[i].energyUsage;
    return total;
}

float BuildingSystem::getAverageComfort() const {
    float total = 0.0f;
    for (int i = 0; i < buildingCount; i++) total += buildings[i].comfortScore;
    return total / buildingCount;
}

SmartBuildingData& BuildingSystem::getBuilding(int index) {
    if (index < 0 || index >= buildingCount) index = 0;
    return buildings[index];
}
