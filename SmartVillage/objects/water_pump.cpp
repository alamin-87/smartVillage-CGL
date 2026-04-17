#include "water_pump.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

WaterPump::WaterPump(float x, float y) {
    posX = x; posY = y;
    handleAngle = 0.0f;
    waterLevel = 0.0f;
    pumping = false;
}

void WaterPump::update(bool isActive) {
    pumping = isActive;
    if (pumping) {
        handleAngle += 3.0f;
        if (handleAngle > 360.0f) handleAngle -= 360.0f;
        waterLevel += 0.002f;
        if (waterLevel > 0.04f) waterLevel = 0.04f;
    } else {
        waterLevel -= 0.001f;
        if (waterLevel < 0.0f) waterLevel = 0.0f;
    }
}

void WaterPump::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Concrete base slab
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-0.06f, 0.0f);
        glVertex2f( 0.06f, 0.0f);
        glVertex2f( 0.06f, 0.015f);
        glVertex2f(-0.06f, 0.015f);
    glEnd();

    // Vertical pipe
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.015f);
        glVertex2f( 0.01f, 0.015f);
        glVertex2f( 0.01f, 0.12f);
        glVertex2f(-0.01f, 0.12f);
    glEnd();

    // Pump head
    glColor3f(0.25f, 0.25f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.10f);
        glVertex2f( 0.02f, 0.10f);
        glVertex2f( 0.02f, 0.13f);
        glVertex2f(-0.02f, 0.13f);
    glEnd();

    // Spout
    glColor3f(0.35f, 0.35f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(0.02f, 0.08f);
        glVertex2f(0.06f, 0.08f);
        glVertex2f(0.06f, 0.09f);
        glVertex2f(0.02f, 0.09f);
    glEnd();

    // Handle arm (animated)
    glPushMatrix();
    glTranslatef(0.0f, 0.12f, 0.0f);
    float swing = sin(handleAngle * 3.14159f / 180.0f) * 20.0f;
    glRotatef(swing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    drawBresenhamLine(0.0f, 0.0f, -0.06f, 0.02f);
    // Handle grip
    glColor3f(0.5f, 0.3f, 0.1f);
    fillMidpointCircle(-0.06f, 0.02f, 0.008f);
    glPopMatrix();

    // Water stream from spout (when pumping)
    if (pumping && sin(handleAngle * 3.14159f / 180.0f) < 0) {
        glColor3f(0.3f, 0.6f, 0.9f);
        glBegin(GL_LINES);
            glVertex2f(0.06f, 0.08f);
            glVertex2f(0.06f, 0.02f);
        glEnd();
        // Splash particles
        for (int i = 0; i < 3; i++) {
            float sx = 0.05f + i * 0.01f;
            glBegin(GL_POINTS);
                glVertex2f(sx, 0.02f);
            glEnd();
        }
    }

    // Bucket
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.03f, 0.0f);
        glVertex2f(0.07f, 0.0f);
        glVertex2f(0.065f, 0.04f);
        glVertex2f(0.035f, 0.04f);
    glEnd();
    // Water in bucket
    if (waterLevel > 0.0f) {
        glColor3f(0.2f, 0.5f, 0.9f);
        glBegin(GL_QUADS);
            glVertex2f(0.035f, 0.005f);
            glVertex2f(0.065f, 0.005f);
            glVertex2f(0.065f, 0.005f + waterLevel);
            glVertex2f(0.035f, 0.005f + waterLevel);
        glEnd();
    }

    glPopMatrix();
}
