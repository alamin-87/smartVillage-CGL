#include "goat.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Goat::Goat(float x, float y) {
    posX = x; posY = y; baseY = y;
    moveTime = 0.0f; hopTimer = 0.0f; hopping = false;
}

void Goat::update() {
    moveTime += 0.03f;
    posX += 0.001f * sin(moveTime);
    
    hopTimer += 0.05f;
    if (!hopping && rand() % 200 == 0) hopping = true;
    if (hopping) {
        posY = baseY + fabsf(sin(hopTimer * 2.0f)) * 0.04f;
        if (sin(hopTimer * 2.0f) < 0.01f && hopTimer > 1.0f) {
            hopping = false; posY = baseY; hopTimer = 0.0f;
        }
    }
}

void Goat::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);

    // Body
    glPushMatrix();
    glScalef(1.6f, 1.0f, 1.0f);
    glColor3f(0.75f, 0.7f, 0.65f);
    fillMidpointCircle(0.0f, 0.04f, 0.035f);
    glPopMatrix();

    // Legs
    glColor3f(0.5f, 0.45f, 0.4f);
    drawBresenhamLine(-0.04f, 0.01f, -0.04f, -0.04f);
    drawBresenhamLine(-0.02f, 0.01f, -0.02f, -0.04f);
    drawBresenhamLine( 0.02f, 0.01f,  0.02f, -0.04f);
    drawBresenhamLine( 0.04f, 0.01f,  0.04f, -0.04f);

    // Head
    glColor3f(0.7f, 0.65f, 0.6f);
    fillMidpointCircle(0.07f, 0.06f, 0.02f);

    // Horns (spikes)
    glColor3f(0.9f, 0.85f, 0.7f);
    drawBresenhamLine(0.065f, 0.08f, 0.055f, 0.11f);
    drawBresenhamLine(0.075f, 0.08f, 0.085f, 0.11f);

    // Beard
    glColor3f(0.5f, 0.45f, 0.4f);
    drawBresenhamLine(0.08f, 0.05f, 0.085f, 0.03f);
    drawBresenhamLine(0.08f, 0.05f, 0.09f, 0.035f);

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);
    fillMidpointCircle(0.078f, 0.065f, 0.003f);

    // Tail
    glColor3f(0.6f, 0.55f, 0.5f);
    float tailA = sin(moveTime * 4.0f) * 10.0f;
    glPushMatrix();
    glTranslatef(-0.06f, 0.06f, 0.0f);
    glRotatef(tailA, 0.0f, 0.0f, 1.0f);
    drawBresenhamLine(0.0f, 0.0f, -0.02f, 0.025f);
    glPopMatrix();

    glPopMatrix();
}
