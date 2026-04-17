#include "lighting_system.h"
#include <GL/glut.h>
#include "../algorithms/midpoint_circle.h"

LightingSystem::LightingSystem(float x, float y) {
    posX = x;
    posY = y;
    lightOn = false;
}

void LightingSystem::update(bool isNight) {
    lightOn = isNight;
}

void LightingSystem::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Draw pole
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f( 0.01f, 0.0f);
        glVertex2f( 0.01f, 0.3f);
        glVertex2f(-0.01f, 0.3f);
    glEnd();

    // Draw lamp head
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.3f);
        glVertex2f( 0.05f, 0.3f);
        glVertex2f( 0.03f, 0.35f);
        glVertex2f(-0.03f, 0.35f);
    glEnd();

    // Draw light beam if ON
    if (lightOn) {
        // Bright yellow bulb
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.28f, 0.0f);
        drawMidpointCircle(0.0f, 0.0f, 0.03f);
        glTranslatef(0.0f, -0.28f, 0.0f);

        // Light cone
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 0.2f, 0.3f); // Transparent yellow

        glBegin(GL_TRIANGLES);
            glVertex2f( 0.0f,  0.28f);
            glVertex2f(-0.15f, 0.0f);
            glVertex2f( 0.15f, 0.0f);
        glEnd();
        
        glDisable(GL_BLEND);
    }

    glPopMatrix();
}
