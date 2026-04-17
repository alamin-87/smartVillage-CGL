#include "hen.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Hen::Hen(float x, float y) {
    posX = x; posY = y;
    peckTime = 0.0f; moveTime = 0.0f; pecking = true;
}

void Hen::update() {
    moveTime += 0.04f;
    peckTime += 0.15f;
    posX += sin(moveTime * 0.5f) * 0.001f;
    if (rand() % 100 == 0) pecking = !pecking;
}

void Hen::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);

    // Body
    glPushMatrix();
    glScalef(1.3f, 1.0f, 1.0f);
    glColor3f(0.8f, 0.5f, 0.2f);
    fillMidpointCircle(0.0f, 0.02f, 0.025f);
    glPopMatrix();

    // Head (pecking animation)
    float headDip = pecking ? fabsf(sin(peckTime)) * 0.015f : 0.0f;
    glColor3f(0.85f, 0.55f, 0.25f);
    fillMidpointCircle(0.03f, 0.04f - headDip, 0.015f);

    // Comb (red triangle)
    glColor3f(0.9f, 0.15f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.025f, 0.055f - headDip);
        glVertex2f(0.035f, 0.055f - headDip);
        glVertex2f(0.03f, 0.07f - headDip);
    glEnd();

    // Wattle
    glColor3f(0.9f, 0.2f, 0.15f);
    fillMidpointCircle(0.035f, 0.03f - headDip, 0.004f);

    // Beak
    glColor3f(0.95f, 0.7f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.04f, 0.04f - headDip);
        glVertex2f(0.055f, 0.038f - headDip);
        glVertex2f(0.04f, 0.035f - headDip);
    glEnd();

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);
    fillMidpointCircle(0.035f, 0.045f - headDip, 0.003f);

    // Wing
    glColor3f(0.7f, 0.4f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.02f);
        glVertex2f(0.01f, 0.02f);
        glVertex2f(-0.005f, 0.04f);
    glEnd();

    // Tail feathers
    glColor3f(0.6f, 0.35f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, 0.02f);
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(-0.04f, 0.01f);
    glEnd();

    // Legs
    glColor3f(0.9f, 0.6f, 0.1f);
    drawBresenhamLine(-0.005f, 0.0f, -0.01f, -0.03f);
    drawBresenhamLine( 0.01f, 0.0f,  0.005f, -0.03f);
    // Feet claws
    drawBresenhamLine(-0.01f, -0.03f, -0.02f, -0.035f);
    drawBresenhamLine(-0.01f, -0.03f,  0.0f,  -0.035f);
    drawBresenhamLine( 0.005f,-0.03f, -0.005f,-0.035f);
    drawBresenhamLine( 0.005f,-0.03f,  0.015f,-0.035f);

    glPopMatrix();
}
