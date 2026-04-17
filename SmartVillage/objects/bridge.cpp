#include "bridge.h"
#include <GL/glut.h>
#include "../algorithms/bresenham.h"

void Bridge::render() {

    glColor3f(0.6f, 0.4f, 0.2f);

    // horizontal planks
    for (float i = -0.3f; i <= 0.3f; i += 0.05f) {
        drawBresenhamLine(i, -0.5f, i, -0.7f);
    }

    // top support
    drawBresenhamLine(-0.3f, -0.5f, 0.3f, -0.5f);
}
