#include "alamin.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Alamin::Alamin(float x, float y) {
    posX = x; posY = y;
    targetX = x; moveTime = 0.0f; isWalking = false;
}

void Alamin::setTarget(float tx) {
    targetX = tx;
    isWalking = true;
}

void Alamin::update() {
    float dx = targetX - posX;
    if (fabs(dx) > 0.01f) {
        isWalking = true;
        moveTime += 0.2f;
        posX += (dx > 0) ? 0.01f : -0.01f;
    } else {
        isWalking = false;
        posX = targetX;
        moveTime = 0.0f;
    }
}

void Alamin::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(1.2f, 1.2f, 1.2f); // Make him a bit bigger to stand out as main character

    float legSwing = isWalking ? sin(moveTime) * 15.0f : 0.0f;
    float armSwing = isWalking ? -sin(moveTime) * 15.0f : 0.0f;
    int facing = (targetX >= posX) ? 1 : -1;
    glScalef((float)facing, 1.0f, 1.0f);

    // Torso (School Shirt - White)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.015f, 0.0f);
        glVertex2f( 0.015f, 0.0f);
        glVertex2f( 0.015f, 0.04f);
        glVertex2f(-0.015f, 0.04f);
    glEnd();

    // Tie (Red)
    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.005f, 0.035f);
        glVertex2f( 0.005f, 0.035f);
        glVertex2f( 0.0f,   0.01f);
    glEnd();

    // School Bag (Blue, on back)
    glColor3f(0.1f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.01f);
        glVertex2f(-0.01f, 0.01f);
        glVertex2f(-0.01f, 0.035f);
        glVertex2f(-0.025f, 0.035f);
    glEnd();

    // Back Arm
    glPushMatrix();
    glTranslatef(0.0f, 0.03f, 0.0f);
    glRotatef(-armSwing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.8f, 0.6f, 0.4f);
    drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.03f);
    glPopMatrix();

    // Back Leg (Pants - Dark Blue)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(-legSwing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.1f, 0.2f, 0.4f);
    drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.04f);
    glPopMatrix();

    // Front Leg (Pants)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(legSwing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.15f, 0.25f, 0.45f);
    drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.04f);
    glPopMatrix();

    // Head
    glColor3f(0.85f, 0.65f, 0.45f); // Skin tone
    fillMidpointCircle(0.0f, 0.05f, 0.015f);

    // Hair (Black)
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.015f, 0.05f);
        glVertex2f( 0.015f, 0.05f);
        glVertex2f( 0.0f,   0.07f);
    glEnd();

    // Front Arm
    glPushMatrix();
    glTranslatef(0.0f, 0.03f, 0.0f);
    glRotatef(armSwing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.85f, 0.65f, 0.45f);
    drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.03f);
    glPopMatrix();

    glPopMatrix();
}
