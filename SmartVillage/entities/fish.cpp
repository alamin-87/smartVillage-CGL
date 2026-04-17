#include "fish.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"

Fish::Fish(float x, float y, float r, float g, float b) {
    posX = x;
    posY = y;
    baseY = y;
    colorR = r; colorG = g; colorB = b;
    speed = 0.003f + (rand() % 100) / 40000.0f;
    swimTime = (rand() % 100) / 10.0f;
    jumping = false;
    jumpTime = 0.0f;
}

void Fish::update() {
    swimTime += 0.04f;
    posX += speed;
    
    // Realistic Dive Cycle
    float wave = sin(swimTime);
    if (wave < 0.0f) {
        // Diving phase: Goes deep
        posY = baseY + wave * 0.15f;
    } else {
        // Surface phase: Floating
        posY = baseY + wave * 0.02f;
    }
    
    if (posX > 7.0f) posX = -7.0f;
    if (posX < -7.0f) posX = 7.0f;

    if (!jumping && rand() % 800 == 0) {
        jumping = true;
        jumpTime = 0.0f;
    }
    if (jumping) {
        jumpTime += 0.1f;
        posY = baseY + 0.2f * sin(jumpTime);
        if (jumpTime > 3.14159f) jumping = false;
    }
}

void Fish::render() {
    // Visibility based on depth
    float depthAlpha = 1.0f;
    if (!jumping) {
        float depth = baseY - posY;
        if (depth > 0.01f) {
            depthAlpha = 1.0f - (depth * 8.0f); // Becomes invisible as it dives
            if (depthAlpha < 0.0f) depthAlpha = 0.0f;
        }
    }

    if (depthAlpha <= 0.0f) return;

    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Body
    glPushMatrix();
    glScalef(1.5f, 1.0f, 1.0f);
    glColor4f(colorR, colorG, colorB, depthAlpha);
    fillMidpointCircle(0.0f, 0.0f, 0.015f);
    glPopMatrix();

    // Tail
    glColor4f(colorR * 0.8f, colorG * 0.8f, colorB * 0.8f, depthAlpha);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.025f, 0.0f); glVertex2f(-0.04f, 0.012f); glVertex2f(-0.04f, -0.012f);
    glEnd();

    // Eye
    glColor4f(0.0f, 0.0f, 0.0f, depthAlpha);
    fillMidpointCircle(0.01f, 0.004f, 0.004f);

    glDisable(GL_BLEND);
    glPopMatrix();
}
