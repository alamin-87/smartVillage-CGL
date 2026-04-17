#include "cowshed.h"
#include <GL/glut.h>
#include "../algorithms/bresenham.h"

CowShed::CowShed(float x, float y) { posX = x; posY = y; }

void CowShed::render(bool gateOpen) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Back wall
    glColor3f(0.55f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.0f);
        glVertex2f( 0.15f, 0.0f);
        glVertex2f( 0.15f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
    glEnd();

    // Thatched roof
    glColor3f(0.45f, 0.35f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.18f, 0.15f);
        glVertex2f( 0.18f, 0.15f);
        glVertex2f( 0.0f,  0.25f);
    glEnd();
    // Roof texture lines
    glColor3f(0.35f, 0.25f, 0.08f);
    for (float h = 0.16f; h < 0.24f; h += 0.02f) {
        float w = 0.18f * (0.25f - h) / 0.10f;
        drawBresenhamLine(-w, h, w, h);
    }

    // Gate frame (GL_LINES)
    glColor3f(0.3f, 0.2f, 0.1f);
    if (gateOpen) {
        // Open gate - just the frame
        drawBresenhamLine(-0.06f, 0.0f, -0.06f, 0.10f);
        drawBresenhamLine( 0.06f, 0.0f,  0.06f, 0.10f);
        drawBresenhamLine(-0.06f, 0.10f, 0.06f, 0.10f);
    } else {
        // Closed gate with cross beams
        drawBresenhamLine(-0.06f, 0.0f, -0.06f, 0.10f);
        drawBresenhamLine( 0.06f, 0.0f,  0.06f, 0.10f);
        drawBresenhamLine(-0.06f, 0.10f, 0.06f, 0.10f);
        // Cross
        drawBresenhamLine(-0.06f, 0.0f,  0.06f, 0.10f);
        drawBresenhamLine( 0.06f, 0.0f, -0.06f, 0.10f);
        // Horizontal bars
        drawBresenhamLine(-0.06f, 0.033f, 0.06f, 0.033f);
        drawBresenhamLine(-0.06f, 0.066f, 0.06f, 0.066f);
    }

    // Hay bale inside
    glColor3f(0.85f, 0.75f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(0.07f, 0.0f);
        glVertex2f(0.13f, 0.0f);
        glVertex2f(0.13f, 0.06f);
        glVertex2f(0.07f, 0.06f);
    glEnd();
    // Hay texture
    glColor3f(0.7f, 0.6f, 0.2f);
    drawBresenhamLine(0.08f, 0.02f, 0.12f, 0.04f);
    drawBresenhamLine(0.09f, 0.01f, 0.11f, 0.05f);

    // Tether post
    glColor3f(0.4f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.12f, 0.0f);
        glVertex2f(-0.11f, 0.0f);
        glVertex2f(-0.11f, 0.08f);
        glVertex2f(-0.12f, 0.08f);
    glEnd();

    glPopMatrix();
}
