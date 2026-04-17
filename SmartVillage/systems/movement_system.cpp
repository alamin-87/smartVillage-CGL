#include "movement_system.h"
#include <cmath>
#include <cstdlib>

// --- PatrolMovement ---
PatrolMovement::PatrolMovement(float startX, float startY, float endX, float endY, float speed) 
    : startX(startX), startY(startY), endX(endX), endY(endY), speed(speed) {
    currentX = startX;
    currentY = startY;
    progress = 0.0f;
    movingForward = true;
}

void PatrolMovement::update(float dt) {
    float step = speed * dt;
    if (movingForward) {
        progress += step;
        if (progress >= 1.0f) {
            progress = 1.0f;
            movingForward = false;
        }
    } else {
        progress -= step;
        if (progress <= 0.0f) {
            progress = 0.0f;
            movingForward = true;
        }
    }
    currentX = startX + (endX - startX) * progress;
    currentY = startY + (endY - startY) * progress;
}

// --- WanderMovement ---
WanderMovement::WanderMovement(float centerX, float centerY, float radius, float speed)
    : centerX(centerX), centerY(centerY), radius(radius), speed(speed) {
    angle = (float)(rand() % 360);
    currentX = centerX;
    currentY = centerY;
}

void WanderMovement::update(float dt) {
    angle += speed * dt * 30.0f;
    // Lissajous-style wandering for natural movement
    currentX = centerX + radius * sin(angle * 0.017453f);
    currentY = centerY + radius * 0.5f * sin(angle * 0.017453f * 1.7f);
}
