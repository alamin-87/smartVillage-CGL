#include "pole.h"
#include <GL/glut.h>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Pole::Pole(float x, float y) { posX = x; posY = y; }

void Pole::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Main pole
    glColor3f(0.45f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.012f, 0.0f);
        glVertex2f( 0.012f, 0.0f);
        glVertex2f( 0.012f, 0.35f);
        glVertex2f(-0.012f, 0.35f);
    glEnd();

    // Cross arm
    glColor3f(0.4f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.32f);
        glVertex2f( 0.08f, 0.32f);
        glVertex2f( 0.08f, 0.335f);
        glVertex2f(-0.08f, 0.335f);
    glEnd();

    // Insulators (small circles)
    glColor3f(0.3f, 0.3f, 0.3f);
    fillMidpointCircle(-0.07f, 0.34f, 0.008f);
    fillMidpointCircle( 0.07f, 0.34f, 0.008f);
    fillMidpointCircle(-0.03f, 0.34f, 0.008f);
    fillMidpointCircle( 0.03f, 0.34f, 0.008f);

    // Power lines going off-screen
    glColor3f(0.15f, 0.15f, 0.15f);
    drawBresenhamLine(-0.07f, 0.34f, -1.0f, 0.30f);
    drawBresenhamLine( 0.07f, 0.34f,  1.0f, 0.30f);
    drawBresenhamLine(-0.03f, 0.34f, -1.0f, 0.28f);
    drawBresenhamLine( 0.03f, 0.34f,  1.0f, 0.28f);

    glPopMatrix();
}
