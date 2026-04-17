#include "boat.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Boat::Boat(float x, float y) {
    posX = x;
    posY = y;
    swayAngle = 0.0f;
    speed = 0.0005f;
}

void Boat::update() {
    swayAngle += 0.05f;
    posX += speed;
    if (posX > 1.3f) posX = -1.3f;
}

void Boat::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    
    float sway = sin(swayAngle) * 2.0f;
    glRotatef(sway, 0.0f, 0.0f, 1.0f);

    // Hull (trapezoid)
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f( 0.08f, 0.0f);
        glVertex2f( 0.06f, -0.03f);
        glVertex2f(-0.06f, -0.03f);
    glEnd();

    // Hull bottom edge
    glColor3f(0.4f, 0.2f, 0.1f);
    drawBresenhamLine(-0.06f, -0.03f, 0.06f, -0.03f);

    // Mast
    glColor3f(0.4f, 0.25f, 0.1f);
    drawBresenhamLine(0.0f, 0.0f, 0.0f, 0.1f);

    // Sail (triangle)
    glColor3f(0.95f, 0.9f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.0f, 0.02f);
        glVertex2f(0.06f, 0.04f);
    glEnd();

    // Sail lines
    glColor3f(0.5f, 0.5f, 0.5f);
    drawBresenhamLine(0.0f, 0.1f, 0.06f, 0.04f);
    drawBresenhamLine(0.0f, 0.02f, 0.06f, 0.04f);

    // Fisherman
    drawFisherman();

    // Navigation light at night
    if (isNight) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 0.5f, 0.7f);
        fillMidpointCircle(-0.04f, 0.02f, 0.015f);
        glDisable(GL_BLEND);
    }

    // Ripple rings around boat
    glColor3f(0.3f, 0.6f, 1.0f);
    float rippleR = 0.1f + sin(swayAngle * 0.5f) * 0.02f;
    fillMidpointCircle(0.0f, -0.03f, rippleR);

    glPopMatrix();
}

void Boat::drawFisherman() {
    // Seated body
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(-0.02f, 0.0f);
        glVertex2f(-0.02f, 0.04f);
        glVertex2f(-0.04f, 0.04f);
    glEnd();

    // Head
    glColor3f(0.9f, 0.7f, 0.5f);
    fillMidpointCircle(-0.03f, 0.055f, 0.015f);

    // Hat
    glColor3f(0.4f, 0.3f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, 0.06f);
        glVertex2f(-0.01f, 0.06f);
        glVertex2f(-0.03f, 0.085f);
    glEnd();

    // Fishing rod
    glColor3f(0.3f, 0.2f, 0.1f);
    drawBresenhamLine(-0.02f, 0.04f, 0.07f, 0.08f);

    // Fishing line
    glColor3f(0.7f, 0.7f, 0.7f);
    float rodTip = sin(swayAngle * 2.0f) * 0.01f;
    drawBresenhamLine(0.07f, 0.08f, 0.07f + rodTip, -0.05f);
}
