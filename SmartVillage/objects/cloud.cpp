#include "cloud.h"
#include <GL/glut.h>
#include "../algorithms/midpoint_circle.h"
#include <cstdlib>

Cloud::Cloud(float x, float y, float size) {
    posX = x;
    posY = y;
    scale = size;
    speed = 0.001f + (static_cast<float>(rand() % 100) / 100000.0f);
}

void Cloud::update(bool isWindy, bool isStormy) {
    float currentSpeed = speed;
    if (isStormy) currentSpeed *= 15.0f;
    else if (isWindy) currentSpeed *= 5.0f;

    posX += currentSpeed;
    if (posX > 1.3f) {
        posX = -1.3f;
    }
}

void Cloud::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Layered fluff with volume shading
    for (int i = 0; i < 6; i++) {
        float xOff = (i - 3) * 0.04f;
        float yOff = (i % 2 == 0) ? 0.02f : -0.02f;
        float circleScale = 0.08f + (i * 0.005f);
        
        // Base shadow
        glColor4f(0.85f, 0.85f, 0.9f, 0.6f); 
        fillMidpointCircle(xOff, yOff - 0.01f, circleScale);
        
        // Highlight
        glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
        fillMidpointCircle(xOff, yOff, circleScale);
    }

    glPopMatrix();
    glDisable(GL_BLEND);
}

