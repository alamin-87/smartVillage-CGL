#include "midpoint_circle.h"
#include <GL/glut.h>

void drawSymmetricPoints(float xc, float yc, float x, float y) {
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc - x);
    glVertex2f(xc - y, yc - x);
}

// xc, yc, r are floats typically in [-1, 1], so we need to map them to pixels to run integer math
// But for OpenGL immediate mode, we can just use steps. Let's do a pseudo-midpoint or proper 
// mathematical midpoint that maps into [-1, 1] bounds.
void drawMidpointCircle(float xc, float yc, float r) {
    // Treat the screen as 1000x1000 grid for the algorithm
    int R = (int)(r * 500); 
    int Xc = (int)(xc * 500);
    int Yc = (int)(yc * 500);

    int x = 0;
    int y = R;
    int p = 1 - R;

    glBegin(GL_POINTS);
    drawSymmetricPoints(xc, yc, x/500.0f, y/500.0f);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawSymmetricPoints(xc, yc, x/500.0f, y/500.0f);
    }
    glEnd();
}

void drawSymmetricLines(float xc, float yc, float x, float y) {
    glVertex2f(xc - x, yc + y);
    glVertex2f(xc + x, yc + y);
    glVertex2f(xc - x, yc - y);
    glVertex2f(xc + x, yc - y);
    glVertex2f(xc - y, yc + x);
    glVertex2f(xc + y, yc + x);
    glVertex2f(xc - y, yc - x);
    glVertex2f(xc + y, yc - x);
}

void fillMidpointCircle(float xc, float yc, float r) {
    int R = (int)(r * 500); 
    int Xc = (int)(xc * 500);
    int Yc = (int)(yc * 500);

    int x = 0;
    int y = R;
    int p = 1 - R;

    glBegin(GL_LINES);
    drawSymmetricLines(xc, yc, x/500.0f, y/500.0f);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawSymmetricLines(xc, yc, x/500.0f, y/500.0f);
    }
    glEnd();
}

