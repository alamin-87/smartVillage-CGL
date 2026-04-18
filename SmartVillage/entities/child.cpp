#include "child.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"
#include "../systems/sound_manager.h"

Child::Child(float startX, float startY, int variety) {
    posX = startX;
    posY = startY;
    startYBase = startY;
    baseSpeed = 0.004f; // Stable, not fast movement
    legAngle = 0.0f;
    jumpOffset = 0.0f;
    jumpTime = (float)(rand() % 100) / 10.0f; 
    isPlaying = false;
    childScale = 0.7f;
    isSitting = false;
    this->variety = variety;
    direction = rand() % 4;
    stateTimer = 150 + rand() % 200; // Walk for longer periods

    if (variety == 0) { // Orange
        shirtR = 0.9f; shirtG = 0.6f; shirtB = 0.1f;
    } else if (variety == 1) { // Blue
        shirtR = 0.1f; shirtG = 0.5f; shirtB = 0.9f;
    } else if (variety == 2) { // Green
        shirtR = 0.2f; shirtG = 0.8f; shirtB = 0.3f;
    } else { // Purple/Pink
        shirtR = 0.8f; shirtG = 0.2f; shirtB = 0.8f;
    }
}

void Child::pickNewDirection() {
    direction = rand() % 4;
    stateTimer = 150 + rand() % 200;
}

void Child::update() {
    if (isSitting) {
        jumpOffset = 0.0f;
        legAngle = 0.0f;
        return;
    }

    if (baseSpeed != 0.0f && !isPlaying) {
        stateTimer--;
        if (stateTimer <= 0) {
            pickNewDirection();
        }

        float speedX = 0, speedY = 0;
        if (direction == 0) speedX = baseSpeed;
        else if (direction == 1) speedX = -baseSpeed;
        else if (direction == 2) speedY = -baseSpeed * 0.4f; // Slower Y walk
        else if (direction == 3) speedY = baseSpeed * 0.4f;

        posX += speedX;
        posY += speedY;

        if (posX > maxX) posX = minX;
        if (posX < minX) posX = maxX;

        float localMinY = startYBase - 0.1f;
        float localMaxY = startYBase + 0.1f;
        if (localMinY < minY) localMinY = minY;
        if (localMaxY > maxY) localMaxY = maxY;

        if (posY > localMaxY) { posY = localMaxY; pickNewDirection(); }
        if (posY < localMinY) { posY = localMinY; pickNewDirection(); }

        jumpTime += 0.08f; // Slower bounce
        jumpOffset = fabsf(sin(jumpTime * 1.5f) * 0.015f);
        legAngle = sin(jumpTime * 2.0f) * 20.0f;

        // Keyboard-controlled sounds now, auto-trigger disabled
        /*
        if (rand() % 4000 == 0) { 
            SoundManager::getInstance().playChild();
        }
        */
    } else if (isPlaying) {
        jumpTime += 0.15f;
        jumpOffset = fabsf(sin(jumpTime * 2.5f) * 0.03f);
        legAngle = sin(jumpTime * 3.0f) * 15.0f;

        /*
        if (rand() % 1500 == 0) {
            SoundManager::getInstance().playChild();
        }
        */
    } else {
        jumpOffset = 0.0f;
        legAngle = 0.0f;
    }
}

void Child::renderSideView(float skinR, float skinG, float skinB) {
    glColor3f(shirtR, shirtG, shirtB); 
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.05f); glVertex2f( 0.04f, 0.05f);
        glVertex2f( 0.05f, 0.18f); glVertex2f(-0.05f, 0.18f);
    glEnd();

    if (variety == 0 || variety == 2) {
        glColor3f(1.0f, 1.0f, 1.0f); drawBresenhamLine(-0.045f, 0.12f, 0.045f, 0.12f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); fillMidpointCircle(0.0f, 0.11f, 0.015f);
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.22f, 0.0f);
    if (variety == 1 || variety == 3) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.05f, 0.0f); glVertex2f(-0.06f, 0.05f);
            glVertex2f(-0.03f, 0.08f); glVertex2f(0.03f, 0.08f);
            glVertex2f(0.06f, 0.05f); glVertex2f(0.05f, 0.0f);
        glEnd();
    } else {
        glColor3f(0.2f, 0.1f, 0.05f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.045f, 0.01f); glVertex2f(-0.05f, 0.05f);
            glVertex2f(-0.02f, 0.07f); glVertex2f(0.02f, 0.07f);
            glVertex2f(0.05f, 0.05f); glVertex2f(0.045f, 0.01f);
        glEnd();
    }
    glColor3f(skinR, skinG, skinB); fillMidpointCircle(0.0f, 0.0f, 0.045f);
    glColor3f(0.1f, 0.1f, 0.1f);
    fillMidpointCircle(-0.018f, 0.005f, 0.006f); fillMidpointCircle(0.018f, 0.005f, 0.006f);
    glPopMatrix();

    glColor3f(0.2f, 0.3f, 0.7f); // Shorts
    glPushMatrix();
        glTranslatef(-0.02f, 0.05f, 0.0f); glRotatef(legAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS); glVertex2f(-0.015f, 0.0f); glVertex2f(0.015f, 0.0f); glVertex2f(0.012f, -0.04f); glVertex2f(-0.012f, -0.04f); glEnd();
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f, 0.0f, -0.1f);
        glColor3f(0.2f, 0.2f, 0.2f); drawBresenhamLine(-0.01f, -0.1f, 0.02f, -0.1f);
    glPopMatrix();
    glColor3f(0.2f, 0.3f, 0.7f);
    glPushMatrix();
        glTranslatef(0.02f, 0.05f, 0.0f); glRotatef(-legAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS); glVertex2f(-0.015f, 0.0f); glVertex2f(0.015f, 0.0f); glVertex2f(0.012f, -0.04f); glVertex2f(-0.012f, -0.04f); glEnd();
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f, 0.0f, -0.1f);
        glColor3f(0.2f, 0.2f, 0.2f); drawBresenhamLine(-0.01f, -0.1f, 0.02f, -0.1f);
    glPopMatrix();

    float armAngle = -legAngle * 1.2f;
    glColor3f(skinR, skinG, skinB);
    glPushMatrix(); glTranslatef(-0.05f, 0.17f, 0.0f); glRotatef(armAngle, 0.0f, 0.0f, 1.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.09f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.05f, 0.17f, 0.0f); glRotatef(-armAngle, 0.0f, 0.0f, 1.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.09f); glPopMatrix();
}

void Child::renderFrontView(float skinR, float skinG, float skinB) {
    glColor3f(shirtR, shirtG, shirtB);
    glBegin(GL_POLYGON); glVertex2f(-0.05f, 0.05f); glVertex2f( 0.05f, 0.05f); glVertex2f( 0.05f, 0.18f); glVertex2f(-0.05f, 0.18f); glEnd();
    
    if (variety == 0 || variety == 2) {
        glColor3f(1.0f, 1.0f, 1.0f); drawBresenhamLine(-0.05f, 0.12f, 0.05f, 0.12f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); fillMidpointCircle(0.0f, 0.11f, 0.015f);
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.22f, 0.0f);
    if (variety == 1 || variety == 3) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_POLYGON); glVertex2f(-0.055f, 0.01f); glVertex2f(-0.05f, 0.06f); glVertex2f(0.0f, 0.075f); glVertex2f(0.05f, 0.06f); glVertex2f(0.055f, 0.01f); glVertex2f(0.0f, 0.035f); glEnd();
    } else {
        glColor3f(0.2f, 0.1f, 0.05f);
        glBegin(GL_POLYGON); glVertex2f(-0.05f, 0.01f); glVertex2f(-0.045f, 0.06f); glVertex2f(0.0f, 0.07f); glVertex2f(0.045f, 0.06f); glVertex2f(0.05f, 0.01f); glEnd();
    }
    glColor3f(skinR, skinG, skinB); fillMidpointCircle(0.0f, 0.0f, 0.045f);
    glColor3f(0.1f, 0.1f, 0.1f); fillMidpointCircle(-0.018f, 0.005f, 0.006f); fillMidpointCircle(0.018f, 0.005f, 0.006f);
    glPopMatrix();

    float legSwing = sin(legAngle * 3.14159f / 180.0f) * 0.015f;
    glPushMatrix();
        glTranslatef(-0.025f, 0.05f, 0.0f); glColor3f(0.2f, 0.3f, 0.7f); glRectf(-0.015f, 0.0f, 0.015f, -0.04f + legSwing);
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f + legSwing, 0.0f, -0.09f + legSwing);
        glColor3f(0.2f, 0.2f, 0.2f); drawBresenhamLine(-0.01f, -0.09f + legSwing, 0.01f, -0.09f + legSwing);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.025f, 0.05f, 0.0f); glColor3f(0.2f, 0.3f, 0.7f); glRectf(-0.015f, 0.0f, 0.015f, -0.04f - legSwing);
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f - legSwing, 0.0f, -0.09f - legSwing);
        glColor3f(0.2f, 0.2f, 0.2f); drawBresenhamLine(-0.01f, -0.09f - legSwing, 0.01f, -0.09f - legSwing);
    glPopMatrix();

    glColor3f(skinR, skinG, skinB);
    float armSwing = -legSwing * 1.5f;
    glPushMatrix(); glTranslatef(-0.06f, 0.17f, 0.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.08f + armSwing); glPopMatrix();
    glPushMatrix(); glTranslatef(0.06f, 0.17f, 0.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.08f - armSwing); glPopMatrix();
}

void Child::renderBackView(float skinR, float skinG, float skinB) {
    glColor3f(shirtR * 0.9f, shirtG * 0.9f, shirtB * 0.9f);
    glBegin(GL_POLYGON); glVertex2f(-0.05f, 0.05f); glVertex2f( 0.05f, 0.05f); glVertex2f( 0.05f, 0.18f); glVertex2f(-0.05f, 0.18f); glEnd();

    glPushMatrix();
    glTranslatef(0.0f, 0.22f, 0.0f);
    if (variety == 1 || variety == 3) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_POLYGON); glVertex2f(-0.055f, -0.01f); glVertex2f(-0.05f, 0.06f); glVertex2f(0.0f, 0.075f); glVertex2f(0.05f, 0.06f); glVertex2f(0.055f, -0.01f); glVertex2f(0.0f, -0.03f); glEnd();
    } else {
        glColor3f(0.2f, 0.1f, 0.05f);
        glBegin(GL_POLYGON); glVertex2f(-0.05f, -0.01f); glVertex2f(-0.045f, 0.06f); glVertex2f(0.0f, 0.07f); glVertex2f(0.045f, 0.06f); glVertex2f(0.05f, -0.01f); glVertex2f(0.0f, -0.04f); glEnd();
    }
    glPopMatrix();

    float legSwing = sin(-legAngle * 3.14159f / 180.0f) * 0.015f;
    glPushMatrix();
        glTranslatef(-0.025f, 0.05f, 0.0f); glColor3f(0.15f, 0.25f, 0.65f); glRectf(-0.015f, 0.0f, 0.015f, -0.04f + legSwing);
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f + legSwing, 0.0f, -0.09f + legSwing);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.025f, 0.05f, 0.0f); glColor3f(0.15f, 0.25f, 0.65f); glRectf(-0.015f, 0.0f, 0.015f, -0.04f - legSwing);
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(0.0f, -0.04f - legSwing, 0.0f, -0.09f - legSwing);
    glPopMatrix();

    glColor3f(skinR * 0.9f, skinG * 0.9f, skinB * 0.9f);
    float armSwing = -legSwing * 1.5f;
    glPushMatrix(); glTranslatef(-0.06f, 0.17f, 0.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.08f + armSwing); glPopMatrix();
    glPushMatrix(); glTranslatef(0.06f, 0.17f, 0.0f); drawBresenhamLine(0.0f, 0.0f, 0.0f, -0.08f - armSwing); glPopMatrix();
}

void Child::render() {
    glPushMatrix();
    glTranslatef(posX, posY + jumpOffset, 0.0f);
    glScalef(childScale, childScale, 1.0f); 

    float skinR = 0.95f, skinG = 0.75f, skinB = 0.65f;

    if (isSitting) {
        glColor3f(0.2f, 0.3f, 0.7f); glBegin(GL_POLYGON); glVertex2f(-0.04f, 0.05f); glVertex2f( 0.04f, 0.05f); glVertex2f( 0.09f, -0.02f); glVertex2f( 0.06f, -0.05f); glVertex2f(-0.06f, -0.05f); glVertex2f(-0.09f, -0.02f); glEnd();
        glColor3f(skinR, skinG, skinB); drawBresenhamLine(-0.05f, 0.16f, -0.08f, 0.07f); drawBresenhamLine(0.05f, 0.16f, 0.08f, 0.07f);
        glColor3f(shirtR, shirtG, shirtB); glBegin(GL_POLYGON); glVertex2f(-0.04f, 0.05f); glVertex2f( 0.04f, 0.05f); glVertex2f( 0.05f, 0.18f); glVertex2f(-0.05f, 0.18f); glEnd();
        glPushMatrix(); glTranslatef(0.0f, 0.22f, 0.0f); glColor3f(skinR, skinG, skinB); fillMidpointCircle(0.0f, 0.0f, 0.045f); glColor3f(0.1f, 0.1f, 0.1f); glBegin(GL_POLYGON); glVertex2f(-0.045f, 0.01f); glVertex2f(-0.05f, 0.05f); glVertex2f(0.0f, 0.07f); glVertex2f(0.05f, 0.05f); glVertex2f(0.045f, 0.01f); glEnd(); glPopMatrix();
    } else {
        if (direction == 0) { renderSideView(skinR, skinG, skinB); }
        else if (direction == 1) { glPushMatrix(); glScalef(-1.0f, 1.0f, 1.0f); renderSideView(skinR, skinG, skinB); glPopMatrix(); }
        else if (direction == 2) { renderFrontView(skinR, skinG, skinB); }
        else if (direction == 3) { renderBackView(skinR, skinG, skinB); }
    }
    glPopMatrix();
}
