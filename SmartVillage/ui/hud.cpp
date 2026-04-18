#include "hud.h"
#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "../smart/energy_system.h"
#include "../smart/building_system.h"

void HUD::render(float sunAngle, bool isRainy, bool isStormy, bool isWindy) {
    // Premium Semi-Transparent Panel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Header panel
    glColor4f(0.1f, 0.1f, 0.2f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f( 1.0f, 1.0f);
        glVertex2f( 1.0f, 0.85f);
        glVertex2f(-1.0f, 0.85f);
    glEnd();

    // Left Status Panel
    glColor4f(0.05f, 0.05f, 0.1f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.95f, 0.82f);
        glVertex2f(-0.55f, 0.82f);
        glVertex2f(-0.55f, 0.48f);
        glVertex2f(-0.95f, 0.48f);
    glEnd();
    glDisable(GL_BLEND);

    // Title
    glColor3f(0.0f, 1.0f, 0.8f);
    drawText(-0.9f, 0.93f, "DIGITAL TWIN: SMART VILLAGE SIMULATOR");
    
    // Scene indicator
    glColor3f(0.8f, 0.8f, 0.8f);
    drawText(0.5f, 0.93f, "[1-3] Scenes [D/N] Time [R/S/W] Weather");

    // Real-time Clock
    char timeStr[50];
    int normalizedHour = ((int)(sunAngle / 15) + 6) % 24;
    int minutes = (int)(fmod(sunAngle, 15.0f) / 15.0f * 60.0f);
    sprintf(timeStr, "CLOCK: %02d:%02d", normalizedHour, minutes);
    
    if (normalizedHour >= 6 && normalizedHour < 18) {
        glColor3f(1.0f, 0.9f, 0.2f);
    } else {
        glColor3f(0.6f, 0.7f, 1.0f);
    }
    drawText(-0.9f, 0.75f, timeStr);

    // Day/Night period
    const char* period;
    if (normalizedHour >= 5 && normalizedHour < 7) period = "DAWN";
    else if (normalizedHour >= 7 && normalizedHour < 12) period = "MORNING";
    else if (normalizedHour >= 12 && normalizedHour < 14) period = "NOON";
    else if (normalizedHour >= 14 && normalizedHour < 17) period = "AFTERNOON";
    else if (normalizedHour >= 17 && normalizedHour < 19) period = "DUSK";
    else period = "NIGHT";
    
    char periodStr[50];
    sprintf(periodStr, "PERIOD: %s", period);
    glColor3f(0.8f, 0.8f, 0.5f);
    drawText(-0.9f, 0.70f, periodStr);

    // Weather Status
    const char* wStatus = "CLEAR SKY";
    if (isStormy) {
        wStatus = "STORM WARNING";
        glColor3f(1.0f, 0.2f, 0.2f);
    } else if (isRainy && isWindy) {
        wStatus = "RAIN + WIND";
        glColor3f(0.5f, 0.6f, 1.0f);
    } else if (isRainy) {
        wStatus = "RAINING";
        glColor3f(0.4f, 0.6f, 1.0f);
    } else if (isWindy) {
        wStatus = "WINDY";
        glColor3f(0.8f, 0.8f, 0.8f);
    } else {
        glColor3f(0.2f, 1.0f, 0.2f);
    }
    char wStr[50];
    sprintf(wStr, "WEATHER: %s", wStatus);
    drawText(-0.9f, 0.65f, wStr);

    // Temperature (from weather system or estimated)
    float temp = 30.0f;
    if (isRainy) temp -= 5.0f;
    if (isStormy) temp -= 8.0f;
    if (normalizedHour >= 18 || normalizedHour < 6) temp -= 6.0f;
    char tempStr[50];
    sprintf(tempStr, "TEMP: %.0f C", temp);
    glColor3f(1.0f, 0.7f, 0.3f);
    drawText(-0.9f, 0.60f, tempStr);

    // Population count
    BuildingSystem& bs = BuildingSystem::getInstance();
    char popStr[50];
    sprintf(popStr, "POPULATION: %d active", bs.getTotalOccupants());
    glColor3f(0.7f, 0.9f, 1.0f);
    drawText(-0.9f, 0.55f, popStr);

    // Building comfort
    char comfortStr[50];
    sprintf(comfortStr, "COMFORT: %.0f%%", bs.getAverageComfort());
    float comfort = bs.getAverageComfort();
    if (comfort > 80.0f) glColor3f(0.2f, 1.0f, 0.2f);
    else if (comfort > 50.0f) glColor3f(1.0f, 1.0f, 0.2f);
    else glColor3f(1.0f, 0.2f, 0.2f);
    drawText(-0.9f, 0.50f, comfortStr);

    // Energy Dashboard (right side)
    EnergySystem::getInstance().renderDashboard(0.52f, 0.55f);

    // Keyboard Function Controls (Bottom Right)
    glEnable(GL_BLEND);
    glColor4f(0.0f, 0.05f, 0.1f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(0.55f, -0.65f);
        glVertex2f(0.95f, -0.65f);
        glVertex2f(0.95f, -0.95f);
        glVertex2f(0.55f, -0.95f);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(0.57f, -0.62f, "SYSTEM CONTROLS");
    
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(0.57f, -0.70f, "[1,2,3] : Change Scene");
    drawText(0.57f, -0.75f, "[C, B, H]: Toggle Child/Bird/Hen Audio");
    drawText(0.57f, -0.80f, "[D, N]   : Force Day/Night");
    drawText(0.57f, -0.85f, "[R,S,W] : Weather Effects");
    drawText(0.57f, -0.90f, "[ESC]   : Power Off System");
}

void HUD::drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
