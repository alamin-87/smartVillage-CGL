#include "building.h"
#include <GL/glut.h>
#include <cstdlib>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Building::Building(float x, float y, int floors, float width, int type) {
    posX = x; posY = y;
    numFloors = floors; bWidth = width; bType = type;
}

void Building::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    float bHeight = numFloors * 0.15f;

    // Shadow
    glColor3f(0.1f, 0.1f, 0.1f);
    if (!isNight) {
        glBegin(GL_QUADS);
            glVertex2f(bWidth, 0.0f);
            glVertex2f(bWidth + 0.1f, 0.0f);
            glVertex2f(bWidth + 0.1f, bHeight * 0.5f);
            glVertex2f(bWidth, bHeight * 0.5f);
        glEnd();
    }

    // Main Structure
    if (bType == 0) glColor3f(0.6f, 0.6f, 0.65f); // Office
    else glColor3f(0.7f, 0.65f, 0.6f);             // Apartment

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(bWidth, 0.0f);
        glVertex2f(bWidth, bHeight);
        glVertex2f(0.0f, bHeight);
    glEnd();

    // Windows
    int cols = (int)(bWidth / 0.06f);
    for (int f = 0; f < numFloors; f++) {
        for (int c = 0; c < cols; c++) {
            float wx = 0.02f + c * 0.06f;
            float wy = 0.04f + f * 0.15f;

            // Window light logic
            bool windowOn = isNight && (rand() % 3 != 0); // 66% on at night
            
            if (windowOn) {
                if (bType == 0) glColor3f(0.9f, 0.9f, 1.0f); // Cool white for office
                else glColor3f(1.0f, 0.9f, 0.5f);            // Warm yellow for apt
            } else if (!isNight) {
                glColor3f(0.4f, 0.5f, 0.6f); // Reflect sky
            } else {
                glColor3f(0.1f, 0.1f, 0.1f); // Dark
            }

            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.04f, wy);
                glVertex2f(wx + 0.04f, wy + 0.06f);
                glVertex2f(wx, wy + 0.06f);
            glEnd();

            glColor3f(0.2f, 0.2f, 0.2f);
            glBegin(GL_LINE_LOOP);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.04f, wy);
                glVertex2f(wx + 0.04f, wy + 0.06f);
                glVertex2f(wx, wy + 0.06f);
            glEnd();
        }
    }

    // Rooftop features
    if (bType == 0) { // Antenna for office
        glColor3f(0.3f, 0.3f, 0.3f);
        drawBresenhamLine(bWidth / 2.0f, bHeight, bWidth / 2.0f, bHeight + 0.15f);
        fillMidpointCircle(bWidth / 2.0f, bHeight + 0.15f, 0.01f);
    } else { // Water tank for apartment
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
            glVertex2f(bWidth * 0.2f, bHeight);
            glVertex2f(bWidth * 0.8f, bHeight);
            glVertex2f(bWidth * 0.8f, bHeight + 0.08f);
            glVertex2f(bWidth * 0.2f, bHeight + 0.08f);
        glEnd();
        glColor3f(0.4f, 0.4f, 0.45f);
        fillMidpointCircle(bWidth * 0.5f, bHeight + 0.04f, 0.04f);
    }

    glPopMatrix();
}
