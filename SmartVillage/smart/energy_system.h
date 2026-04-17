#ifndef ENERGY_SYSTEM_H
#define ENERGY_SYSTEM_H

#include <GL/glut.h>

// Smart Energy Grid - tracks power generation, consumption, and renders dashboard
class EnergySystem {
public:
    static EnergySystem& getInstance();

    void update(float dt, bool isNight, bool isStormy, int activeLights, int activeBuildings);
    void renderDashboard(float x, float y); // Renders a mini energy panel on HUD

    float getTotalLoad() const { return totalLoad; }
    float getSolarOutput() const { return solarOutput; }
    float getGridEfficiency() const;
    const char* getGridStatus() const;

private:
    EnergySystem();
    float totalLoad;         // kWh
    float solarOutput;       // kW
    float windOutput;        // kW
    float baseLoad;          // kW
    int lightsActive;
    int buildingsActive;
    float animTimer;
};

#endif
