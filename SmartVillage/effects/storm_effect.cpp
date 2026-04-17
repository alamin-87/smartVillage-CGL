#include "storm_effect.h"
#include <GL/glut.h>
#include <cstdlib>

StormEffect::StormEffect() {
    flashTimer = 0;
    flashActive = false;
}

void StormEffect::update() {
    // Random lightning flash
    if (!flashActive && (rand() % 200) == 0) {
        flashActive = true;
        flashTimer = 10; // Frames to flash
    }

    if (flashActive) {
        flashTimer--;
        if (flashTimer <= 0) {
            flashActive = false;
        }
    }
}

void StormEffect::render() {
    if (flashActive) {
        // Draw white transparent overlay
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glColor4f(1.0f, 1.0f, 1.0f, 0.6f); // white flash with 60% opacity
        
        glBegin(GL_QUADS);
            glVertex2f(-1.0f,  1.0f);
            glVertex2f( 1.0f,  1.0f);
            glVertex2f( 1.0f, -1.0f);
            glVertex2f(-1.0f, -1.0f);
        glEnd();

        glDisable(GL_BLEND);
    }
}
