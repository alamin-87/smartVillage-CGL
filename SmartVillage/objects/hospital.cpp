#include "hospital.h"
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

Hospital::Hospital(float x, float y) {
    posX = x; posY = y;
    flashTimer = 0.0f; flashState = false;
}

void Hospital::update(float dt) {
    flashTimer += dt;
    if (flashTimer > 0.5f) { flashState = !flashState; flashTimer = 0.0f; }
}

void Hospital::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Left wing
    glColor3f(0.92f, 0.92f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(-0.1f, 0.3f);
        glVertex2f(-0.35f, 0.3f);
    glEnd();

    // Right wing
    glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.0f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.3f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    // Connecting corridor
    glColor3f(0.88f, 0.88f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f( 0.1f, 0.1f);
        glVertex2f( 0.1f, 0.25f);
        glVertex2f(-0.1f, 0.25f);
    glEnd();

    // Windows on both wings
    for (int wing = 0; wing < 2; wing++) {
        float baseX = (wing == 0) ? -0.33f : 0.12f;
        for (int r = 0; r < 2; r++) {
            for (int c = 0; c < 2; c++) {
                float wx = baseX + c * 0.1f;
                float wy = 0.04f + r * 0.14f;
                if (isNight) glColor3f(0.9f, 0.9f, 0.7f);
                else glColor3f(0.6f, 0.8f, 0.95f);
                glBegin(GL_QUADS);
                    glVertex2f(wx, wy);
                    glVertex2f(wx+0.06f, wy);
                    glVertex2f(wx+0.06f, wy+0.08f);
                    glVertex2f(wx, wy+0.08f);
                glEnd();
                glColor3f(0.4f, 0.4f, 0.4f);
                glBegin(GL_LINE_LOOP);
                    glVertex2f(wx, wy);
                    glVertex2f(wx+0.06f, wy);
                    glVertex2f(wx+0.06f, wy+0.08f);
                    glVertex2f(wx, wy+0.08f);
                glEnd();
            }
        }
    }

    // Emergency entrance canopy
    glColor3f(0.8f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.1f);
        glVertex2f( 0.08f, 0.1f);
        glVertex2f( 0.1f, 0.13f);
        glVertex2f(-0.1f, 0.13f);
    glEnd();

    // Entrance door
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f( 0.04f, 0.0f);
        glVertex2f( 0.04f, 0.1f);
        glVertex2f(-0.04f, 0.1f);
    glEnd();

    // Red cross on facade
    drawCross(0.0f, 0.22f, 0.04f);

    // Hospital sign
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.30f);
        glVertex2f( 0.2f, 0.30f);
        glVertex2f( 0.2f, 0.34f);
        glVertex2f(-0.2f, 0.34f);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.5f);
    const char* name = "DISTRICT GENERAL HOSPITAL";
    glRasterPos2f(-0.19f, 0.315f);
    for (int i = 0; i < (int)strlen(name); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);

    // Helipad on roof
    glColor3f(0.5f, 0.5f, 0.5f);
    fillMidpointCircle(0.0f, 0.36f, 0.03f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.005f, 0.355f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'H');

    // Ambulance
    drawAmbulance(0.2f, -0.02f);

    // Emergency lights (always ON)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.2f, 0.2f, 0.6f);
    fillMidpointCircle(-0.35f, 0.1f, 0.015f);
    fillMidpointCircle( 0.35f, 0.1f, 0.015f);
    glDisable(GL_BLEND);

    glPopMatrix();
}

void Hospital::drawCross(float x, float y, float size) {
    glColor3f(0.9f, 0.1f, 0.1f);
    // Vertical bar
    glBegin(GL_QUADS);
        glVertex2f(x - size*0.25f, y - size);
        glVertex2f(x + size*0.25f, y - size);
        glVertex2f(x + size*0.25f, y + size);
        glVertex2f(x - size*0.25f, y + size);
    glEnd();
    // Horizontal bar
    glBegin(GL_QUADS);
        glVertex2f(x - size, y - size*0.25f);
        glVertex2f(x + size, y - size*0.25f);
        glVertex2f(x + size, y + size*0.25f);
        glVertex2f(x - size, y + size*0.25f);
    glEnd();
    // Circle outline
    glColor3f(0.8f, 0.1f, 0.1f);
    fillMidpointCircle(x, y, size * 1.2f);
}

void Hospital::drawAmbulance(float ax, float ay) {
    glPushMatrix();
    glTranslatef(ax, ay, 0.0f);

    // Van body
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f( 0.08f, 0.0f);
        glVertex2f( 0.08f, 0.06f);
        glVertex2f(-0.08f, 0.06f);
    glEnd();

    // Cab
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(0.08f, 0.0f);
        glVertex2f(0.12f, 0.0f);
        glVertex2f(0.12f, 0.05f);
        glVertex2f(0.08f, 0.05f);
    glEnd();

    // Windshield
    glColor3f(0.6f, 0.8f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(0.09f, 0.02f);
        glVertex2f(0.115f, 0.02f);
        glVertex2f(0.115f, 0.045f);
        glVertex2f(0.09f, 0.045f);
    glEnd();

    // Red cross on side
    drawCross(0.0f, 0.03f, 0.015f);

    // Red stripe
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.055f);
        glVertex2f( 0.08f, 0.055f);
        glVertex2f( 0.08f, 0.06f);
        glVertex2f(-0.08f, 0.06f);
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    fillMidpointCircle(-0.05f, -0.01f, 0.015f);
    fillMidpointCircle( 0.05f, -0.01f, 0.015f);
    // Hubcaps
    glColor3f(0.5f, 0.5f, 0.5f);
    fillMidpointCircle(-0.05f, -0.01f, 0.006f);
    fillMidpointCircle( 0.05f, -0.01f, 0.006f);

    // Roof light bar (flashing)
    if (flashState) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);
    }
    fillMidpointCircle(-0.02f, 0.065f, 0.008f);
    fillMidpointCircle( 0.02f, 0.065f, 0.008f);

    glPopMatrix();
}
