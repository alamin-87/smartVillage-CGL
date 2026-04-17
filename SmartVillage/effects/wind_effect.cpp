#include "wind_effect.h"
#include <GL/glut.h>
#include <cstdlib>
#include "../algorithms/dda.h"

WindEffect::WindEffect() {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x = ((rand() % 200) - 100) / 100.0f;
        particles[i].y = ((rand() % 200) - 100) / 100.0f;
        particles[i].length = ((rand() % 15) + 5) / 100.0f;
        particles[i].speed = ((rand() % 10) + 5) / 100.0f;
    }
}

void WindEffect::update(float strength) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].x += particles[i].speed * strength;

        // Reset if blown off screen
        if (particles[i].x > 1.2f) {
            particles[i].x = -1.2f;
            particles[i].y = ((rand() % 200) - 100) / 100.0f;
        }
    }
}

void WindEffect::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.8f, 0.85f, 0.9f, 0.3f);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        drawDDALine(particles[i].x, particles[i].y,
                    particles[i].x - particles[i].length, particles[i].y + 0.002f);
    }

    glDisable(GL_BLEND);
}
