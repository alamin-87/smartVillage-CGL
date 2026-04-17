#include "yacht.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Yacht::Yacht(float x, float y) : posX(x), posY(y) {
    speed = 0.0003f; // Luxurious slow movement
    swayAngle = 0.0f;
}

void Yacht::update() {
    posX += speed;
    if (posX > 1.5f) posX = -1.5f;
    swayAngle += 0.02f;
}

void Yacht::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY + sin(swayAngle)*0.01f, 0.0f);
    
    // Hull (Sleek White)
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, 0.0f);
        glVertex2f( 0.12f, 0.0f);
        glVertex2f( 0.18f,  0.06f);
        glVertex2f(-0.18f,  0.06f);
    glEnd();
    
    // Bottom Stripe
    if(isNight) glColor3f(0.1f, 0.2f, 0.6f); else glColor3f(0.0f, 0.3f, 0.7f);
    glRectf(-0.16f, 0.01f, 0.14f, 0.025f);

    // Cabin (Upper level)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.10f, 0.06f);
        glVertex2f( 0.08f, 0.06f);
        glVertex2f( 0.06f, 0.11f);
        glVertex2f(-0.08f, 0.11f);
    glEnd();

    // Windows (Reflective Blue)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.4f, 0.7f, 0.9f, 0.7f);
    glRectf(-0.07f, 0.075f, -0.01f, 0.1f);
    glRectf( 0.01f, 0.075f,  0.05f, 0.1f);
    glDisable(GL_BLEND);

    // Mast/Antenna
    glColor3f(0.3f, 0.3f, 0.3f);
    drawBresenhamLine(-0.02f, 0.11f, -0.02f, 0.16f);

    // Cabin Lights at Night
    if (isNight) {
        glEnable(GL_BLEND);
        glColor4f(1.0f, 1.0f, 0.5f, 0.5f);
        fillMidpointCircle(-0.04f, 0.087f, 0.01f);
        fillMidpointCircle(0.03f, 0.087f, 0.01f);
        glDisable(GL_BLEND);
    }

    glPopMatrix();
}
