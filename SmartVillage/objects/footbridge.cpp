#include "footbridge.h"
#include <GL/glut.h>
#include <cmath>

Footbridge::Footbridge(float x, float y, float length) {
    posX = x;
    posY = y;
    bridgeLength = length;
}

void Footbridge::render() {
    float halfLen = bridgeLength / 2.0f;
    float floorHeight = 0.05f;
    float railingHeight = 0.08f;

    // --- Pillars ---
    glColor3f(0.3f, 0.3f, 0.35f); // Steel gray
    // Left Pillar
    glBegin(GL_QUADS);
    glVertex2f(posX - halfLen, posY);
    glVertex2f(posX - halfLen + 0.04f, posY);
    glVertex2f(posX - halfLen + 0.04f, posY - 0.4f);
    glVertex2f(posX - halfLen, posY - 0.4f);
    glEnd();

    // Right Pillar
    glBegin(GL_QUADS);
    glVertex2f(posX + halfLen - 0.04f, posY);
    glVertex2f(posX + halfLen, posY);
    glVertex2f(posX + halfLen, posY - 0.4f);
    glVertex2f(posX + halfLen - 0.04f, posY - 0.4f);
    glEnd();

    // --- Bridge Floor ---
    glColor3f(0.4f, 0.4f, 0.45f);
    glBegin(GL_QUADS);
    glVertex2f(posX - halfLen, posY);
    glVertex2f(posX + halfLen, posY);
    glVertex2f(posX + halfLen, posY - floorHeight);
    glVertex2f(posX - halfLen, posY - floorHeight);
    glEnd();

    // Floor Detail line
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(posX - halfLen, posY - floorHeight);
    glVertex2f(posX + halfLen, posY - floorHeight);
    glEnd();

    // --- Glass Railings ---
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.7f, 1.0f, 0.4f); // Transparent light blue
    glBegin(GL_QUADS);
    glVertex2f(posX - halfLen, posY + railingHeight);
    glVertex2f(posX + halfLen, posY + railingHeight);
    glVertex2f(posX + halfLen, posY);
    glVertex2f(posX - halfLen, posY);
    glEnd();
    glDisable(GL_BLEND);

    // Railing Frame
    glColor3f(0.2f, 0.2f, 0.25f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(posX - halfLen, posY);
    glVertex2f(posX - halfLen, posY + railingHeight);
    glVertex2f(posX + halfLen, posY + railingHeight);
    glVertex2f(posX + halfLen, posY);
    glEnd();
    glLineWidth(1.0f);

    // Vertical supports for railing
    glBegin(GL_LINES);
    for(float x = posX - halfLen + 0.1f; x < posX + halfLen; x += 0.2f) {
        glVertex2f(x, posY);
        glVertex2f(x, posY + railingHeight);
    }
    glEnd();
}
