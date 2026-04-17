#include "traffic_light.h"
#include <GL/glut.h>
#include "../algorithms/midpoint_circle.h"

TrafficLight::TrafficLight(float x, float y) {
    posX = x; posY = y;
    state = 0; // Red
    timer = 0.0f;
}

void TrafficLight::update(float dt) {
    timer += dt;
    if (state == 0 && timer > 300.0f) { state = 2; timer = 0.0f; } // Red to Green
    else if (state == 2 && timer > 250.0f) { state = 1; timer = 0.0f; } // Green to Yellow
    else if (state == 1 && timer > 50.0f) { state = 0; timer = 0.0f; } // Yellow to Red
}

void TrafficLight::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Pole
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f( 0.01f, 0.0f);
        glVertex2f( 0.01f, 0.25f);
        glVertex2f(-0.01f, 0.25f);
    glEnd();

    // Box
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.25f);
        glVertex2f( 0.03f, 0.25f);
        glVertex2f( 0.03f, 0.40f);
        glVertex2f(-0.03f, 0.40f);
    glEnd();

    // Red Light
    if (state == 0) glColor3f(1.0f, 0.0f, 0.0f); else glColor3f(0.3f, 0.0f, 0.0f);
    fillMidpointCircle(0.0f, 0.36f, 0.015f);

    // Yellow Light
    if (state == 1) glColor3f(1.0f, 1.0f, 0.0f); else glColor3f(0.3f, 0.3f, 0.0f);
    fillMidpointCircle(0.0f, 0.325f, 0.015f);

    // Green Light
    if (state == 2) glColor3f(0.0f, 1.0f, 0.0f); else glColor3f(0.0f, 0.3f, 0.0f);
    fillMidpointCircle(0.0f, 0.29f, 0.015f);

    glPopMatrix();
}
