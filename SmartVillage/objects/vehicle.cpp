#include "vehicle.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "../algorithms/midpoint_circle.h"

Vehicle::Vehicle(float x, float y, int type, float speed) : posX(x), posY(y), type(type), speed(speed) {
    wheelRotation = 0.0f;
    // Set colors
    if (type == 0) { // Car
        color[0] = 0.8f; color[1] = 0.1f; color[2] = 0.1f;
    } else if (type == 1) { // Bus
        color[0] = 0.1f; color[1] = 0.6f; color[2] = 0.2f;
    } else if (type == 2) { // Hiace
        color[0] = 0.9f; color[1] = 0.9f; color[2] = 0.9f;
    } else if (type == 3) { // Motorcycle
        color[0] = 0.1f; color[1] = 0.1f; color[2] = 0.1f;
    } else if (type == 4) { // Bicycle
        color[0] = 0.4f; color[1] = 0.4f; color[2] = 0.4f;
    }
}

void Vehicle::update() {
    posX += speed;
    if (speed > 0 && posX > 1.2f) posX = -1.2f;
    if (speed < 0 && posX < -1.2f) posX = 1.2f;
    
    wheelRotation -= speed * 500.0f;
}

void Vehicle::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    
    if (type == 0) drawCar();
    else if (type == 1) drawBus();
    else if (type == 2) drawHiace();
    else if (type == 3) drawMotorcycle();
    else if (type == 4) drawBicycle();
    
    glPopMatrix();
}

void Vehicle::drawCar() {
    glColor3fv(color);
    glBegin(GL_QUADS);
        glVertex2f(-0.06f, 0.015f); glVertex2f( 0.06f, 0.015f);
        glVertex2f( 0.06f, 0.05f); glVertex2f(-0.06f, 0.05f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.05f); glVertex2f( 0.03f, 0.05f);
        glVertex2f( 0.02f, 0.08f); glVertex2f(-0.03f, 0.08f);
    glEnd();
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.025f, 0.052f); glVertex2f( 0.015f, 0.052f);
        glVertex2f( 0.01f,  0.075f); glVertex2f(-0.022f, 0.075f);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.035f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.015f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.035f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.015f); glPopMatrix();
}

void Vehicle::drawBus() {
    glColor3fv(color);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.02f); glVertex2f( 0.15f, 0.02f);
        glVertex2f( 0.15f, 0.12f); glVertex2f(-0.15f, 0.12f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    for(int i=0; i<5; i++) {
        float wx = -0.13f + i * 0.055f;
        glBegin(GL_QUADS);
            glVertex2f(wx, 0.07f); glVertex2f(wx + 0.04f, 0.07f);
            glVertex2f(wx + 0.04f, 0.11f); glVertex2f(wx, 0.11f);
        glEnd();
    }
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.1f, 0.02f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.022f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.06f, 0.02f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.022f); glPopMatrix();
}

void Vehicle::drawHiace() {
    glColor3fv(color);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.02f); glVertex2f( 0.1f, 0.02f);
        glVertex2f( 0.1f, 0.1f); glVertex2f(-0.1f, 0.1f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0.06f, 0.06f); glVertex2f(0.095f, 0.06f);
        glVertex2f(0.095f, 0.09f); glVertex2f(0.055f, 0.09f);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.06f, 0.02f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.018f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.06f, 0.02f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.018f); glPopMatrix();
}

void Vehicle::drawMotorcycle() {
    // Body
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.04f, 0.02f); glVertex2f(0.0f, 0.02f);
        glVertex2f(0.02f, 0.05f); glVertex2f(0.04f, 0.05f);
    glEnd();
    // Rider
    glColor3f(0.2f, 0.3f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.04f); glVertex2f(0.01f, 0.04f);
        glVertex2f(0.005f, 0.08f); glVertex2f(-0.015f, 0.08f);
    glEnd();
    // Helmet
    glColor3f(0.8f, 0.2f, 0.2f);
    fillMidpointCircle(-0.005f, 0.095f, 0.012f);
    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.03f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.012f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.03f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.012f); glPopMatrix();
}

void Vehicle::drawBicycle() {
    // Frame
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.02f, 0.02f); glVertex2f(0.02f, 0.02f);
        glVertex2f(0.0f, 0.06f);
    glEnd();
    // Rider
    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.05f); glVertex2f(0.0f, 0.09f);
    glEnd();
    fillMidpointCircle(0.0f, 0.1f, 0.01f);
    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.025f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.012f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.025f, 0.015f, 0.0f); glRotatef(wheelRotation, 0,0,1); fillMidpointCircle(0,0,0.012f); glPopMatrix();
}
