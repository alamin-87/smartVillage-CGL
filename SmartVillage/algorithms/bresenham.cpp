#include "bresenham.h"
#include <GL/glut.h>
#include <cmath>

// Convert float coordinates [-1, 1] to integer scales for Bresenham, then draw.
void drawBresenhamLine(float x1, float y1, float x2, float y2) {
    int X1 = (int)(x1 * 500);
    int Y1 = (int)(y1 * 500);
    int X2 = (int)(x2 * 500);
    int Y2 = (int)(y2 * 500);

    int dx = abs(X2 - X1);
    int dy = abs(Y2 - Y1);
    
    int sx = (X1 < X2) ? 1 : -1;
    int sy = (Y1 < Y2) ? 1 : -1;
    
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2f(X1 / 500.0f, Y1 / 500.0f);
        if (X1 == X2 && Y1 == Y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            X1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            Y1 += sy;
        }
    }
    glEnd();
}
