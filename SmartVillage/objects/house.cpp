#include "house.h"
#include <GL/glut.h>

House::House(float x, float y) {
    posX = x;
    posY = y;
}

void House::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // 🧱 Base
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.0f);
        glVertex2f( 0.15f, 0.0f);
        glVertex2f( 0.15f, 0.2f);
        glVertex2f(-0.15f, 0.2f);
    glEnd();

    // 🏚️ Siding lines for wood texture
    glColor3f(0.7f, 0.4f, 0.2f);
    glBegin(GL_LINES);
    for(float h = 0.04f; h < 0.2f; h += 0.04f) {
        glVertex2f(-0.15f, h);
        glVertex2f( 0.15f, h);
    }
    glEnd();

    // 🏗️ Chimney
    glColor3f(0.4f, 0.2f, 0.1f);
    glRectf(0.06f, 0.2f, 0.12f, 0.3f);

    // 🔺 Roof

    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.18f, 0.2f);
        glVertex2f( 0.18f, 0.2f);
        glVertex2f( 0.0f, 0.35f);
    glEnd();

    // 🚪 Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.0f);
        glVertex2f( 0.03f, 0.0f);
        glVertex2f( 0.03f, 0.1f);
        glVertex2f(-0.03f, 0.1f);
    glEnd();

    // 🪟 Windows (Glowing at night)
    if (isNight) {
        glColor3f(1.0f, 1.0f, 0.0f); // Bright yellow glow
    } else {
        glColor3f(0.2f, 0.2f, 0.2f); // Dark windows during day
    }

    // Left Window
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.12f);
        glVertex2f(-0.05f, 0.12f);
        glVertex2f(-0.05f, 0.17f);
        glVertex2f(-0.1f, 0.17f);
    glEnd();

    // Right Window
    glBegin(GL_QUADS);
        glVertex2f( 0.05f, 0.12f);
        glVertex2f( 0.1f, 0.12f);
        glVertex2f( 0.1f, 0.17f);
        glVertex2f( 0.05f, 0.17f);
    glEnd();

    glPopMatrix();
}
