#include "tree.h"
#include <GL/glut.h>
#include <cmath>

Tree::Tree(float x, float y) {
    posX = x;
    posY = y;
    angle = 0.0f;
}

// Animation (wind effect)
void Tree::update(bool isWindy) {
    if (isWindy) {
        angle += 0.2f; // faster sway in wind
    } else {
        angle += 0.05f; // gentle sway normally
    }
}

// Draw tree
void Tree::render() {

    float sway = 5.0f * sin(angle); // smooth movement

    glPushMatrix();

    // Move tree to position
    glTranslatef(posX, posY, 0.0f);

    // Apply wind rotation
    glRotatef(sway, 0.0f, 0.0f, 1.0f);

    // 🌳 Trunk
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.0f);
        glVertex2f( 0.02f, 0.0f);
        glVertex2f( 0.02f, 0.2f);
        glVertex2f(-0.02f, 0.2f);
    glEnd();

    // 🌿 Leaves (Multi-layered for realism)
    for (int i = 0; i < 3; i++) {
        float yOff = i * 0.08f;
        float width = 0.12f - (i * 0.02f);
        
        // Shadow layer
        glColor3f(0.0f, 0.4f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-width, 0.15f + yOff);
            glVertex2f( width, 0.15f + yOff);
            glVertex2f( 0.0f,  0.35f + yOff);
        glEnd();

        // Highlight layer
        glColor3f(0.0f, 0.6f + (i * 0.1f), 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(-width + 0.01f, 0.16f + yOff);
            glVertex2f( width - 0.01f, 0.16f + yOff);
            glVertex2f( 0.0f,          0.33f + yOff);
        glEnd();
    }


    glPopMatrix();
}
