#include "animation_system.h"
#include <cmath>

// --- WalkCycle ---
WalkCycle::WalkCycle() : legAngle(0), armAngle(0), bobOffset(0), speed(2.0f), active(false) {}

void WalkCycle::update(float dt) {
    if (!active) {
        // Smoothly return to idle
        legAngle *= 0.9f;
        armAngle *= 0.9f;
        bobOffset *= 0.9f;
        return;
    }
    float t = dt * speed * 60.0f; // normalize to ~60fps
    legAngle = sin(t) * 20.0f;
    armAngle = -sin(t) * 15.0f;
    bobOffset = fabsf(sin(t * 2.0f)) * 0.005f;
}

void WalkCycle::start() { active = true; }
void WalkCycle::stop() { active = false; }

// --- SwayAnimation ---
SwayAnimation::SwayAnimation(float speed, float amplitude) 
    : angle(0), speed(speed), amplitude(amplitude) {}

void SwayAnimation::update(float dt) {
    angle += speed * dt * 60.0f;
}

float SwayAnimation::getAngle() const {
    return amplitude * sin(angle * 0.05f);
}

// --- BobAnimation ---
BobAnimation::BobAnimation(float speed, float amplitude) 
    : offset(0), speed(speed), amplitude(amplitude), timer(0) {}

void BobAnimation::update(float dt) {
    timer += speed * dt * 60.0f;
    offset = amplitude * sin(timer * 0.1f);
}

float BobAnimation::getOffset() const {
    return offset;
}
