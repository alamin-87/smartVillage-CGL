#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

// Provides reusable animation state for walk cycles, bobbing, swaying, etc.
struct WalkCycle {
    float legAngle;
    float armAngle;
    float bobOffset;
    float speed;
    bool active;

    WalkCycle();
    void update(float dt);
    void start();
    void stop();
};

struct SwayAnimation {
    float angle;
    float speed;
    float amplitude;

    SwayAnimation(float speed = 1.0f, float amplitude = 5.0f);
    void update(float dt);
    float getAngle() const;
};

struct BobAnimation {
    float offset;
    float speed;
    float amplitude;
    float timer;

    BobAnimation(float speed = 2.0f, float amplitude = 0.01f);
    void update(float dt);
    float getOffset() const;
};

#endif
