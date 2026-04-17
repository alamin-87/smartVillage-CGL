#ifndef BUILDING_SYSTEM_H
#define BUILDING_SYSTEM_H

// Smart building management - tracks occupancy, energy usage, and comfort
struct SmartBuildingData {
    float temperature;
    float energyUsage;       // kW
    int occupants;
    bool acOn;
    bool lightsOn;
    float comfortScore;      // 0-100

    SmartBuildingData();
    void update(float dt, bool isNight, float outsideTemp);
    float getComfortScore() const { return comfortScore; }
};

class BuildingSystem {
public:
    static BuildingSystem& getInstance();

    void update(float dt, bool isNight, float outsideTemp);
    
    int getTotalOccupants() const;
    float getTotalEnergy() const;
    float getAverageComfort() const;
    
    // Access individual building data
    SmartBuildingData& getBuilding(int index);
    int getBuildingCount() const { return buildingCount; }

private:
    BuildingSystem();
    static const int MAX_BUILDINGS = 10;
    SmartBuildingData buildings[MAX_BUILDINGS];
    int buildingCount;
};

#endif
