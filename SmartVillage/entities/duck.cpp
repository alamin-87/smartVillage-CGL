#include "duck.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"
#include "../systems/sound_manager.h"

Duck::Duck(float x, float y) {
    posX = x; posY = y;
    waddleTime = 0.0f; swimOffset = 0.0f; swimming = false;
}

void Duck::update() {
    if (rand() % 1500 == 0) SoundManager::getInstance().playDuck();
    waddleTime += 0.08f;
    posX += 0.001f;
    if (posX > 0.8f) posX = -0.8f;
    swimOffset = sin(waddleTime) * 0.005f;
}

void Duck::render() {
    glPushMatrix();
    float waddle = sin(waddleTime * 2.0f) * 3.0f;
    glTranslatef(posX, posY + swimOffset, 0.0f);
    glRotatef(waddle, 0.0f, 0.0f, 1.0f);

    // Body (oval)
    glPushMatrix();
    glScalef(1.4f, 1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 0.9f);
    fillMidpointCircle(0.0f, 0.0f, 0.02f);
    glPopMatrix();

    // Head
    glColor3f(0.1f, 0.5f, 0.15f);
    fillMidpointCircle(0.03f, 0.02f, 0.012f);

    // Bill (flat triangle)
    glColor3f(0.9f, 0.6f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.04f, 0.02f);
        glVertex2f(0.06f, 0.025f);
        glVertex2f(0.06f, 0.015f);
    glEnd();

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);
    fillMidpointCircle(0.035f, 0.025f, 0.003f);

    // Wing
    glColor3f(0.9f, 0.9f, 0.8f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.01f);
        glVertex2f(0.01f, 0.01f);
        glVertex2f(-0.005f, 0.03f);
    glEnd();

    // Tail
    glColor3f(0.85f, 0.85f, 0.75f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, 0.005f);
        glVertex2f(-0.04f, 0.015f);
        glVertex2f(-0.04f, -0.005f);
    glEnd();

    // Webbed feet
    glColor3f(0.9f, 0.5f, 0.1f);
    drawBresenhamLine(-0.01f, -0.02f, -0.02f, -0.03f);
    drawBresenhamLine( 0.01f, -0.02f,  0.0f, -0.03f);

    glPopMatrix();
}
