#include "cow.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

Cow::Cow(float x, float y) {
    posX = x; posY = y; baseX = x;
    moveTime = 0.0f; tailSwing = 0.0f; headBob = 0.0f;
    inShed = false;
}

void Cow::update(bool isNight) {
    moveTime += 0.02f;
    tailSwing = sin(moveTime * 3.0f) * 15.0f;
    headBob = sin(moveTime * 2.0f) * 0.01f;
    inShed = isNight;
    if (!inShed) {
        posX = baseX + sin(moveTime * 0.5f) * 0.15f;
    }
}

void Cow::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Body (large ellipse via scaled circle)
    glPushMatrix();
    glScalef(2.0f, 1.0f, 1.0f);
    glColor3f(0.85f, 0.8f, 0.7f);
    fillMidpointCircle(0.0f, 0.05f, 0.05f); // Solid body
    glPopMatrix();

    // Spots (solid)
    glColor3f(0.45f, 0.3f, 0.15f);
    fillMidpointCircle(-0.04f, 0.06f, 0.015f);
    fillMidpointCircle(0.03f, 0.04f, 0.012f);
    fillMidpointCircle(-0.01f, 0.02f, 0.01f);

    // Legs (Solid Quads)
    glColor3f(0.7f, 0.65f, 0.55f);
    float legW = 0.01f;
    // Back left
    glBegin(GL_QUADS);
        glVertex2f(-0.06f-legW, 0.02f); glVertex2f(-0.06f+legW, 0.02f);
        glVertex2f(-0.06f+legW, -0.06f); glVertex2f(-0.06f-legW, -0.06f);
    glEnd();
    // Back right
    glColor3f(0.6f, 0.55f, 0.45f); // Darker shading for back legs
    glBegin(GL_QUADS);
        glVertex2f(-0.03f-legW, 0.02f); glVertex2f(-0.03f+legW, 0.02f);
        glVertex2f(-0.03f+legW, -0.06f); glVertex2f(-0.03f-legW, -0.06f);
    glEnd();
    // Front left
    glColor3f(0.7f, 0.65f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f( 0.06f-legW, 0.02f); glVertex2f( 0.06f+legW, 0.02f);
        glVertex2f( 0.06f+legW, -0.06f); glVertex2f( 0.06f-legW, -0.06f);
    glEnd();
    // Front right
    glColor3f(0.6f, 0.55f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f( 0.03f-legW, 0.02f); glVertex2f( 0.03f+legW, 0.02f);
        glVertex2f( 0.03f+legW, -0.06f); glVertex2f( 0.03f-legW, -0.06f);
    glEnd();

    // Hooves
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.07f, -0.06f); glVertex2f(-0.05f, -0.06f);
        glVertex2f(-0.05f, -0.07f); glVertex2f(-0.07f, -0.07f);
        // ...
        glVertex2f(-0.04f, -0.06f); glVertex2f(-0.02f, -0.06f);
        glVertex2f(-0.02f, -0.07f); glVertex2f(-0.04f, -0.07f);
        // ...
        glVertex2f(0.05f, -0.06f); glVertex2f(0.07f, -0.06f);
        glVertex2f(0.07f, -0.07f); glVertex2f(0.05f, -0.07f);
        // ...
        glVertex2f(0.02f, -0.06f); glVertex2f(0.04f, -0.06f);
        glVertex2f(0.04f, -0.07f); glVertex2f(0.02f, -0.07f);
    glEnd();

    // Head (solid circle + bob)
    glPushMatrix();
    glTranslatef(0.1f, 0.06f + headBob, 0.0f);
    glColor3f(0.8f, 0.75f, 0.65f);
    fillMidpointCircle(0.0f, 0.0f, 0.025f);
    // Snout
    glColor3f(0.85f, 0.75f, 0.7f);
    fillMidpointCircle(0.015f, -0.01f, 0.015f);

    // Eyes
    glColor3f(0.1f, 0.1f, 0.1f);
    fillMidpointCircle(0.005f, 0.01f, 0.004f);

    // Nostrils
    glColor3f(0.3f, 0.2f, 0.1f);
    fillMidpointCircle(0.02f, -0.005f, 0.002f);
    fillMidpointCircle(0.025f, -0.005f, 0.002f);

    // Horns
    glColor3f(0.9f, 0.85f, 0.7f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.005f, 0.02f); glVertex2f(-0.015f, 0.02f); glVertex2f(-0.025f, 0.04f);
        glVertex2f( 0.005f, 0.02f); glVertex2f( 0.015f, 0.02f); glVertex2f( 0.02f,  0.04f);
    glEnd();

    // Ears
    glColor3f(0.75f, 0.65f, 0.55f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.015f); glVertex2f(-0.03f, 0.01f); glVertex2f(-0.02f, 0.025f);
    glEnd();
    glPopMatrix();

    // Tail (animated swing)
    glPushMatrix();
    glTranslatef(-0.1f, 0.06f, 0.0f);
    glRotatef(tailSwing, 0.0f, 0.0f, 1.0f);
    glColor3f(0.6f, 0.5f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-0.005f, 0.0f); glVertex2f(0.005f, 0.0f);
        glVertex2f(-0.035f, -0.06f); glVertex2f(-0.045f, -0.06f);
    glEnd();
    // Tail tuft
    glColor3f(0.4f, 0.3f, 0.2f);
    fillMidpointCircle(-0.04f, -0.06f, 0.008f);
    glPopMatrix();

    // Udder
    glColor3f(0.95f, 0.85f, 0.8f);
    fillMidpointCircle(0.02f, -0.01f, 0.015f);

    glPopMatrix();
}
