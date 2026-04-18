#include "bird.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"
#include "../systems/sound_manager.h"

Bird::Bird(float x, float y, bool isFlying) {
    posX = x;
    posY = y;
    startY = y;
    this->isFlying = isFlying;
    wingAngle = 0.0f;
    wingDir = 1.0f;
    speed = 0.003f + (float)(rand() % 100) / 20000.0f; 
    flapSpeed = 5.0f + (float)(rand() % 10);
    hoverTime = (float)(rand() % 100);
    hoverOffset = 0.0f;
}

void Bird::update() {
    if (isFlying) {
        posX += speed;
        if (posX > 1.5f) posX = -1.5f;
        
        hoverTime += 0.05f;
        hoverOffset = sin(hoverTime) * 0.02f;
        
        wingAngle += wingDir * flapSpeed;
        if (wingAngle > 35.0f || wingAngle < -20.0f) wingDir *= -1.0f;

        // Keyboard-controlled sounds now, auto-trigger disabled
        /*
        if (rand() % 2000 == 0) {
            SoundManager::getInstance().playBird();
        }
        */
    } else {
        hoverTime += 0.02f;
        wingAngle = sin(hoverTime * 5.0f) * 5.0f; 
        
        /*
        if (rand() % 3000 == 0) {
            SoundManager::getInstance().playBird();
        }
        */
    }
}

void Bird::render() {
    glPushMatrix();
    glTranslatef(posX, posY + hoverOffset, 0.0f);
    
    float scale = isFlying ? 0.35f : 0.28f;
    glScalef(scale, scale, 1.0f);

    // Body Color (Varied)
    if (isFlying) glColor3f(0.1f, 0.1f, 0.1f);
    else glColor3f(0.2f, 0.15f, 0.1f);

    // Tail (Fan shape)
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.02f, 0.0f);
        glVertex2f(-0.08f, 0.03f);
        glVertex2f(-0.08f, -0.03f);
    glEnd();

    // Body (Better oval)
    glPushMatrix();
    glScalef(1.8f, 1.0f, 1.0f);
    fillMidpointCircle(0.0f, 0.0f, 0.022f);
    glPopMatrix();

    // Head
    fillMidpointCircle(0.025f, 0.012f, 0.012f);

    // Beak
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.032f, 0.015f);
        glVertex2f(0.055f, 0.012f);
        glVertex2f(0.032f, 0.009f);
    glEnd();

    // Wings (Segmented/Feathered Look)
    glColor3f(0.15f, 0.15f, 0.15f);
    if (isFlying) {
        // Left Wing
        glPushMatrix();
        glRotatef(wingAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, 0.01f);
            glVertex2f(-0.03f, 0.08f);
            glVertex2f(-0.08f, 0.1f);
            glVertex2f(-0.07f, 0.04f);
            glVertex2f(-0.02f, 0.01f);
        glEnd();
        glPopMatrix();

        // Right Wing
        glPushMatrix();
        glRotatef(-wingAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.0f, -0.01f);
            glVertex2f(-0.03f, -0.08f);
            glVertex2f(-0.08f, -0.1f);
            glVertex2f(-0.07f, -0.04f);
            glVertex2f(-0.02f, -0.01f);
        glEnd();
        glPopMatrix();
    } else {
        // Resting wings (tucked)
        glBegin(GL_POLYGON);
            glVertex2f(-0.04f, 0.015f);
            glVertex2f(0.01f, 0.015f);
            glVertex2f(-0.01f, -0.02f);
            glVertex2f(-0.06f, -0.01f);
        glEnd();
    }

    glPopMatrix();
}
