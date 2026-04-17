#include "market.h"
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Market::Market(float x, float y) {
    posX = x;
    posY = y;
    vendorBob = 0.0f;
}

void Market::update(float dt) {
    vendorBob += 0.1f;
}

void Market::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Market road
    glColor3f(0.55f, 0.4f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-0.45f, -0.02f);
        glVertex2f( 0.45f, -0.02f);
        glVertex2f( 0.45f, -0.08f);
        glVertex2f(-0.45f, -0.08f);
    glEnd();

    // Draw 5 stalls
    drawStall(-0.35f, 0.0f, 0.9f, 0.2f, 0.2f);  // Red canopy
    drawStall(-0.17f, 0.0f, 0.2f, 0.7f, 0.2f);  // Green canopy
    drawStall( 0.0f,  0.0f, 0.2f, 0.2f, 0.9f);  // Blue canopy
    drawStall( 0.17f, 0.0f, 0.9f, 0.8f, 0.1f);  // Yellow canopy
    drawStall( 0.35f, 0.0f, 0.7f, 0.2f, 0.7f);  // Purple canopy

    // Sign board
    drawSign();

    // Stall lanterns at night
    if (isNight) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (float sx = -0.35f; sx <= 0.35f; sx += 0.17f) {
            glColor4f(1.0f, 0.9f, 0.3f, 0.6f);
            fillMidpointCircle(sx, 0.12f, 0.03f);
        }
        glDisable(GL_BLEND);
    }

    // Vendor figures
    for (float sx = -0.35f; sx <= 0.35f; sx += 0.17f) {
        drawVendor(sx, -0.01f);
    }

    glPopMatrix();
}

void Market::drawStall(float x, float y, float r, float g, float b) {
    // Stall counter
    glColor3f(0.6f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.06f, y);
        glVertex2f(x + 0.06f, y);
        glVertex2f(x + 0.06f, y + 0.06f);
        glVertex2f(x - 0.06f, y + 0.06f);
    glEnd();

    // Canopy (trapezoid)
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.08f, y + 0.10f);
        glVertex2f(x + 0.08f, y + 0.10f);
        glVertex2f(x + 0.06f, y + 0.14f);
        glVertex2f(x - 0.06f, y + 0.14f);
    glEnd();

    // Support poles using Bresenham
    glColor3f(0.4f, 0.3f, 0.1f);
    drawBresenhamLine(x - 0.06f, y, x - 0.07f, y + 0.10f);
    drawBresenhamLine(x + 0.06f, y, x + 0.07f, y + 0.10f);

    // Decorative flags
    glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.04f, y + 0.10f);
        glVertex2f(x - 0.02f, y + 0.10f);
        glVertex2f(x - 0.03f, y + 0.07f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 0.02f, y + 0.10f);
        glVertex2f(x + 0.04f, y + 0.10f);
        glVertex2f(x + 0.03f, y + 0.07f);
    glEnd();

    // Goods on counter (small colored rectangles)
    glColor3f(0.9f, 0.5f, 0.1f);
    glRectf(x - 0.04f, y + 0.06f, x - 0.01f, y + 0.08f);
    glColor3f(0.1f, 0.8f, 0.3f);
    glRectf(x + 0.01f, y + 0.06f, x + 0.04f, y + 0.08f);
}

void Market::drawSign() {
    // Sign background
    glColor3f(0.1f, 0.3f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.16f);
        glVertex2f( 0.25f, 0.16f);
        glVertex2f( 0.25f, 0.22f);
        glVertex2f(-0.25f, 0.22f);
    glEnd();

    // Sign border
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.25f, 0.16f);
        glVertex2f( 0.25f, 0.16f);
        glVertex2f( 0.25f, 0.22f);
        glVertex2f(-0.25f, 0.22f);
    glEnd();

    // Sign text
    glColor3f(1.0f, 1.0f, 1.0f);
    const char* text = "GOPAL BHAR MARKET";
    glRasterPos2f(-0.2f, 0.18f);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void Market::drawVendor(float x, float y) {
    float bob = sin(vendorBob + x * 10.0f) * 0.005f;
    
    // Vendor body
    glColor3f(0.7f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, y - 0.04f + bob);
        glVertex2f(x + 0.015f, y - 0.04f + bob);
        glVertex2f(x + 0.015f, y + bob);
        glVertex2f(x - 0.015f, y + bob);
    glEnd();

    // Head
    glColor3f(0.9f, 0.7f, 0.5f);
    fillMidpointCircle(x, y + 0.015f + bob, 0.015f);
}
