#include "hud.h"
#include <GL/glut.h>
#include <cstdio>
#include <cstring>

void HUD::render(float sunAngle, bool isRainy, bool isStormy, bool isWindy) {
    // 🎨 UI Styling: Premium Semi-Transparent Panel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Header Blur-like panel
    glColor4f(0.1f, 0.1f, 0.2f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f( 1.0f, 1.0f);
        glVertex2f( 1.0f, 0.85f);
        glVertex2f(-1.0f, 0.85f);
    glEnd();

    // Side Status Panel
    glColor4f(0.05f, 0.05f, 0.1f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.95f, 0.82f);
        glVertex2f(-0.55f, 0.82f);
        glVertex2f(-0.55f, 0.55f);
        glVertex2f(-0.95f, 0.55f);
    glEnd();
    glDisable(GL_BLEND);

    // 🏷️ Title with Modern Look
    glColor3f(0.0f, 1.0f, 0.8f);
    drawText(-0.9f, 0.93f, "DIGITAL TWIN: SMART VILLAGE SIMULATOR");
    
    // 🕒 Real-time Clock logic
    char timeStr[50];
    int normalizedHour = ((int)(sunAngle / 15) + 6) % 24;
    sprintf(timeStr, "CLOCK: %02d:00", normalizedHour);
    
    if (normalizedHour >= 6 && normalizedHour < 18) {
        glColor3f(1.0f, 0.9f, 0.2f); // Golden for day
    } else {
        glColor3f(0.6f, 0.7f, 1.0f); // Cool blue for night
    }
    drawText(-0.9f, 0.75f, timeStr);

    // ⛅ Weather Status
    const char* wStatus = "CLEAR SKY";
    if (isStormy) {
        wStatus = "STORM WARNING";
        glColor3f(1.0f, 0.2f, 0.2f);
    } else if (isRainy) {
        wStatus = "RAINING";
        glColor3f(0.4f, 0.6f, 1.0f);
    } else if (isWindy) {
        wStatus = "WINDY CONDITIONS";
        glColor3f(0.8f, 0.8f, 0.8f);
    } else {
        glColor3f(0.2f, 1.0f, 0.2f);
    }
    char wStr[50];
    sprintf(wStr, "ENV: %s", wStatus);
    drawText(-0.9f, 0.70f, wStr);

    // ⚡ Energy Stats
    int kwh = 120 + (rand() % 10);
    char stats[50];
    sprintf(stats, "GRID LOAD: %d kWh", kwh);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.9f, 0.65f, stats);

    // 🕹️ Controls Hint
    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(-0.88f, 0.60f, "[1-3] Scenes | [N/D] Time | [R/S/W] Weather");
}

void HUD::drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
