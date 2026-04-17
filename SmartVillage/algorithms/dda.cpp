#include "dda.h"
#include <GL/glut.h>
#include <cmath>

void drawDDALine(float x1, float y1, float x2, float y2) {
    int X1 = (int)(x1 * 500);
    int Y1 = (int)(y1 * 500);
    int X2 = (int)(x2 * 500);
    int Y2 = (int)(y2 * 500);

    int dx = X2 - X1;
    int dy = Y2 - Y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) return;

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float X = X1;
    float Y = Y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(X / 500.0f, Y / 500.0f);
        X += xInc;
        Y += yInc;
    }
    glEnd();
}
