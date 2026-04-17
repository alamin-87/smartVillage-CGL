#include "rain_effect.h"
#include "../algorithms/dda.h"
#include <GL/glut.h>
#include <cstdlib>

RainEffect::RainEffect() {
    for (int i = 0; i < NUM_DROPS; ++i) {
        drops[i].x = ((rand() % 200) - 100) / 100.0f; // [-1.0, 1.0]
        drops[i].y = ((rand() % 200) - 100) / 100.0f; // [-1.0, 1.0]
        drops[i].length = ((rand() % 10) + 5) / 100.0f; // [0.05, 0.15]
        drops[i].speed = ((rand() % 5) + 5) / 100.0f;   // [0.05, 0.1]
    }
}

void RainEffect::update() {
    for (int i = 0; i < NUM_DROPS; ++i) {
        drops[i].y -= drops[i].speed;
        // Reset drop if it falls below screen
        if (drops[i].y < -1.0f) {
            drops[i].y = 1.0f + drops[i].length;
            drops[i].x = ((rand() % 200) - 100) / 100.0f;
        }
    }
}

void RainEffect::render() {
    glColor3f(0.5f, 0.5f, 0.8f); // light blue rain

    for (int i = 0; i < NUM_DROPS; ++i) {
        // Draw drops using DDA algorithm
        drawDDALine(drops[i].x, drops[i].y, drops[i].x, drops[i].y - drops[i].length);
    }
}
