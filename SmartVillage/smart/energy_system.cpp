#include "energy_system.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

EnergySystem::EnergySystem() {
    totalLoad = 120.0f;
    solarOutput = 0.0f;
    windOutput = 0.0f;
    baseLoad = 80.0f;
    lightsActive = 0;
    buildingsActive = 0;
    animTimer = 0.0f;
}

EnergySystem& EnergySystem::getInstance() {
    static EnergySystem instance;
    return instance;
}

void EnergySystem::update(float dt, bool isNight, bool isStormy, int activeLights, int activeBuildings) {
    lightsActive = activeLights;
    buildingsActive = activeBuildings;

    // Solar output: peaks at noon (sunAngle ~90), zero at night
    if (!isNight) {
        solarOutput = 5.0f; // Simplified: full sun during day
    } else {
        solarOutput = 0.0f;
    }

    // Wind output: higher during storms
    if (isStormy) windOutput = 3.0f;
    else windOutput = 0.8f;

    // Calculate total load
    float lightLoad = activeLights * 0.15f;
    float buildingLoad = activeBuildings * 2.5f;
    totalLoad = baseLoad + lightLoad + buildingLoad;

    animTimer += dt;
}

float EnergySystem::getGridEfficiency() const {
    float totalGeneration = solarOutput + windOutput;
    if (totalLoad <= 0.0f) return 100.0f;
    float ratio = (totalGeneration / totalLoad) * 100.0f;
    if (ratio > 100.0f) ratio = 100.0f;
    return ratio;
}

const char* EnergySystem::getGridStatus() const {
    float eff = getGridEfficiency();
    if (eff > 80.0f) return "OPTIMAL";
    if (eff > 50.0f) return "NORMAL";
    if (eff > 20.0f) return "HIGH LOAD";
    return "CRITICAL";
}

void EnergySystem::renderDashboard(float x, float y) {
    // Mini energy dashboard panel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Panel background
    glColor4f(0.05f, 0.1f, 0.15f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 0.42f, y);
        glVertex2f(x + 0.42f, y + 0.22f);
        glVertex2f(x, y + 0.22f);
    glEnd();

    // Panel border
    glColor4f(0.0f, 0.8f, 0.6f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + 0.42f, y);
        glVertex2f(x + 0.42f, y + 0.22f);
        glVertex2f(x, y + 0.22f);
    glEnd();
    glDisable(GL_BLEND);

    // Title
    glColor3f(0.0f, 1.0f, 0.8f);
    glRasterPos2f(x + 0.02f, y + 0.18f);
    const char* title = "SMART ENERGY GRID";
    for (int i = 0; i < (int)strlen(title); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, title[i]);

    // Solar output bar
    char buf[64];
    sprintf(buf, "SOLAR: %.1f kW", solarOutput);
    glColor3f(1.0f, 0.9f, 0.2f);
    glRasterPos2f(x + 0.02f, y + 0.13f);
    for (int i = 0; i < (int)strlen(buf); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, buf[i]);

    // Solar bar
    float barWidth = 0.15f * (solarOutput / 5.0f);
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.25f, y + 0.13f);
        glVertex2f(x + 0.25f + barWidth, y + 0.13f);
        glVertex2f(x + 0.25f + barWidth, y + 0.145f);
        glVertex2f(x + 0.25f, y + 0.145f);
    glEnd();

    // Grid load
    sprintf(buf, "LOAD: %.0f kWh", totalLoad);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x + 0.02f, y + 0.08f);
    for (int i = 0; i < (int)strlen(buf); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, buf[i]);

    // Grid status with color
    float eff = getGridEfficiency();
    const char* status = getGridStatus();
    if (eff > 80.0f) glColor3f(0.2f, 1.0f, 0.2f);
    else if (eff > 50.0f) glColor3f(1.0f, 1.0f, 0.2f);
    else glColor3f(1.0f, 0.2f, 0.2f);
    
    sprintf(buf, "STATUS: %s (%.0f%%)", status, eff);
    glRasterPos2f(x + 0.02f, y + 0.03f);
    for (int i = 0; i < (int)strlen(buf); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, buf[i]);
}
