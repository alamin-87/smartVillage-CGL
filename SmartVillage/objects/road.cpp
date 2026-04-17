#include "road.h"
#include <GL/glut.h>
#include "../algorithms/bresenham.h"

Road::Road(float x, float y, float width) {
    posX = x;
    posY = y;
    roadWidth = width;
}

void Road::render() {
    // 🛣️ Road base (dark gray)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, posY);
        glVertex2f( 1.0f, posY);
        glVertex2f( 1.0f, posY - roadWidth);
        glVertex2f(-1.0f, posY - roadWidth);
    glEnd();

    // 🛣️ Road markings (white dashed lines)
    glColor3f(1.0f, 1.0f, 1.0f);
    float lineY = posY - (roadWidth / 2.0f);
    for (float x = -1.0f; x <= 1.0f; x += 0.2f) {
        drawBresenhamLine(x, lineY, x + 0.1f, lineY);
    }

    // 🛣️ Road borders
    glColor3f(0.4f, 0.4f, 0.4f);
    drawBresenhamLine(-1.0f, posY, 1.0f, posY);
    drawBresenhamLine(-1.0f, posY - roadWidth, 1.0f, posY - roadWidth);
}
