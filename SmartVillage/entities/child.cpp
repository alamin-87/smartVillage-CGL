#include "child.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Child::Child(float startX, float startY) {
    posX = startX;
    posY = startY;
    speed = 0.008f; // Faster than human
    legAngle = 0.0f;
    jumpOffset = 0.0f;
    jumpTime = 0.0f;
}

void Child::update() {
    posX += speed;
    if (posX > 1.2f) posX = -1.2f;

    jumpTime += 0.2f;
    jumpOffset = fabsf(sin(jumpTime) * 0.05f); // Constant jumping
    legAngle = sin(jumpTime * 1.5f) * 30.0f;
}

void Child::render() {
    glPushMatrix();
    glTranslatef(posX, posY + jumpOffset, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f); // 70% size of adult human

    // Body (Red shirt)
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.05f);
        glVertex2f( 0.03f, 0.05f);
        glVertex2f( 0.03f, 0.14f);
        glVertex2f(-0.03f, 0.14f);
    glEnd();

    // Head
    glColor3f(0.9f, 0.7f, 0.6f);
    fillMidpointCircle(0.0f, 0.17f, 0.035f);

    // Legs (Short pants)
    glColor3f(0.1f, 0.4f, 0.1f);
    
    // Left leg
    glPushMatrix();
        glTranslatef(-0.015f, 0.05f, 0.0f);
        glRotatef(legAngle, 0.0f, 0.0f, 1.0f);
        drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.07f);
    glPopMatrix();

    // Right leg
    glPushMatrix();
        glTranslatef(0.015f, 0.05f, 0.0f);
        glRotatef(-legAngle, 0.0f, 0.0f, 1.0f);
        drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.07f);
    glPopMatrix();

    glPopMatrix();
}
