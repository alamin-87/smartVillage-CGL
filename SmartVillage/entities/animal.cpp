#include "animal.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Animal::Animal(float startX, float startY) {
    posX = startX;
    posY = startY;
    speed = 0.003f;
    tailAngle = 0.0f;
    moveTime = 0.0f;
}

void Animal::update() {
    moveTime += 0.05f;
    posX += speed;
    if (posX > 1.2f) posX = -1.2f;

    tailAngle = sin(moveTime * 2.0f) * 15.0f;
}

void Animal::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(0.6f, 0.6f, 1.0f);

    // Body (Rectangle-ish)
    glColor3f(0.9f, 0.9f, 0.9f); // White sheep
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f( 0.1f, 0.0f);
        glVertex2f( 0.1f, 0.1f);
        glVertex2f(-0.1f, 0.1f);
    glEnd();

    // Head
    glTranslatef(0.12f, 0.08f, 0.0f);
    fillMidpointCircle(0.0f, 0.0f, 0.04f);
    
    // Tail
    glPushMatrix();
        glTranslatef(-0.22f, 0.0f, 0.0f);
        glRotatef(tailAngle, 0.0f, 0.0f, 1.0f);
        drawBresenhamLine(0.0f, 0.0f, -0.05f, 0.02f);
    glPopMatrix();

    // Legs
    glTranslatef(-0.12f, -0.08f, 0.0f);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawBresenhamLine(-0.06f, 0.0f, -0.06f, -0.06f);
    drawBresenhamLine(0.06f, 0.0f, 0.06f, -0.06f);

    glPopMatrix();
}
