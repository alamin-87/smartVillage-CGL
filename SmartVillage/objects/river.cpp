#include "river.h"
#include <GL/glut.h>

#include "../algorithms/dda.h"

void River::update() {
    offset += 0.005f;
    if (offset > 0.1f) offset = 0.0f;
}

void River::render() {
    // Main water body
    glColor3f(0.0f, 0.4f, 0.8f);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.5f);
        glVertex2f( 1.0f, -0.5f);
        glVertex2f( 1.0f, -0.7f);
        glVertex2f(-1.0f, -0.7f);
    glEnd();

    // Ripples using DDA
    glColor3f(0.1f, 0.5f, 0.9f);
    for (float i = -1.0f; i < 1.0f; i += 0.2f) {
        float x = i + offset;
        drawDDALine(x, -0.55f, x + 0.1f, -0.55f);
        drawDDALine(x - 0.05f, -0.65f, x + 0.05f, -0.65f);
    }
}
