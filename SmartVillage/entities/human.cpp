#include "human.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Human::Human(float startX, float startY) {
    posX = startX;
    posY = startY;
    speed = 0.005f;
    legAngle = 0.0f;
    legDir = 1.0f;
    isSitting = false;
}

void Human::update() {
    if (isSitting) return;

    posX += speed;
    if (posX > 6.0f) posX = -6.0f;
    if (posX < -6.0f) posX = 6.0f;

    legAngle += legDir * 2.0f;
    if (legAngle > 20.0f || legAngle < -20.0f) legDir *= -1.0f;
}

void Human::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    float scale = 1.1f;
    glScalef(scale, scale, 1.0f);

    // Skin color
    float skinR = 0.85f, skinG = 0.65f, skinB = 0.45f;
    
    // Panjabi / Shirt
    glColor3f(0.9f, 0.9f, 1.0f); // Light blueish white
    glBegin(GL_POLYGON);
        glVertex2f(-0.035f, 0.05f);
        glVertex2f( 0.035f, 0.05f);
        glVertex2f( 0.04f,  0.18f);
        glVertex2f( 0.02f,  0.20f);
        glVertex2f(-0.02f,  0.20f);
        glVertex2f(-0.04f,  0.18f);
    glEnd();

    // Collar detail
    glColor3f(0.8f, 0.8f, 0.9f);
    drawBresenhamLine(-0.02f, 0.20f, 0.0f, 0.16f);
    drawBresenhamLine(0.02f, 0.20f, 0.0f, 0.16f);

    // Head
    glPushMatrix();
    glTranslatef(0.0f, 0.24f, 0.0f);
    glColor3f(skinR, skinG, skinB);
    fillMidpointCircle(0.0f, 0.0f, 0.045f);
    
    // Hair
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.015f);
        glVertex2f(-0.045f, 0.05f);
        glVertex2f(0.0f, 0.06f);
        glVertex2f(0.045f, 0.05f);
        glVertex2f(0.04f, 0.015f);
    glEnd();

    // Eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    fillMidpointCircle(-0.015f, 0.01f, 0.006f);
    fillMidpointCircle(0.015f, 0.01f, 0.006f);
    glPopMatrix();

    if (isSitting) {
        // Sitting Legs (Lungi/Pants)
        glColor3f(0.2f, 0.2f, 0.4f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.035f, 0.05f);
            glVertex2f( 0.035f, 0.05f);
            glVertex2f( 0.08f,  -0.02f);
            glVertex2f( 0.05f,  -0.05f);
            glVertex2f(-0.05f,  -0.05f);
            glVertex2f(-0.08f,  -0.02f);
        glEnd();
        
        // Arms (Resting on counter)
        glColor3f(skinR, skinG, skinB);
        drawBresenhamLine(-0.04f, 0.16f, -0.07f, 0.06f);
        drawBresenhamLine(0.04f, 0.16f, 0.07f, 0.06f);
    } else {
        // Walking Legs
        glColor3f(0.2f, 0.2f, 0.2f);
        // Left Leg
        glPushMatrix();
        glTranslatef(0.015f, 0.05f, 0.0f);
        glRotatef(legAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex2f(-0.012f, 0.0f); glVertex2f(0.012f, 0.0f);
            glVertex2f(0.008f, -0.12f); glVertex2f(-0.008f, -0.12f);
        glEnd();
        // Shoe
        glColor3f(0.3f, 0.15f, 0.05f);
        glTranslatef(0.0f, -0.12f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.01f, 0.0f); glVertex2f(0.01f, 0.0f);
            glVertex2f(0.04f, -0.015f); glVertex2f(-0.01f, -0.02f);
        glEnd();
        glPopMatrix();

        // Right Leg
        glPushMatrix();
        glTranslatef(-0.015f, 0.05f, 0.0f);
        glRotatef(-legAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex2f(-0.012f, 0.0f); glVertex2f(0.012f, 0.0f);
            glVertex2f(0.008f, -0.12f); glVertex2f(-0.008f, -0.12f);
        glEnd();
        // Shoe
        glColor3f(0.3f, 0.15f, 0.05f);
        glTranslatef(0.0f, -0.12f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.04f, -0.015f); glVertex2f(0.01f, 0.0f);
            glVertex2f(-0.01f, 0.0f); glVertex2f(-0.01f, -0.02f);
        glEnd();
        glPopMatrix();

        // Arms (Walking)
        float armAngle = -legAngle;
        glColor3f(skinR, skinG, skinB);
        glPushMatrix();
            glTranslatef(-0.04f, 0.18f, 0.0f);
            glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
                glVertex2f(-0.01f, 0.0f); glVertex2f(0.01f, 0.0f);
                glVertex2f(0.005f, -0.1f); glVertex2f(-0.005f, -0.1f);
            glEnd();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.04f, 0.18f, 0.0f);
            glRotatef(-armAngle, 0.0f, 0.0f, 1.0f);
            glBegin(GL_QUADS);
                glVertex2f(-0.01f, 0.0f); glVertex2f(0.01f, 0.0f);
                glVertex2f(0.005f, -0.1f); glVertex2f(-0.005f, -0.1f);
            glEnd();
        glPopMatrix();
    }

    glPopMatrix();
}
