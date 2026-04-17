#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

// Manages entity movement patterns: patrol, wander, follow path
class PatrolMovement {
public:
    PatrolMovement(float startX, float startY, float endX, float endY, float speed);
    void update(float dt);
    float getX() const { return currentX; }
    float getY() const { return currentY; }
    bool isMovingRight() const { return movingForward; }

private:
    float startX, startY, endX, endY;
    float currentX, currentY;
    float speed;
    float progress; // 0.0 to 1.0
    bool movingForward;
};

class WanderMovement {
public:
    WanderMovement(float centerX, float centerY, float radius, float speed);
    void update(float dt);
    float getX() const { return currentX; }
    float getY() const { return currentY; }

private:
    float centerX, centerY;
    float radius;
    float currentX, currentY;
    float angle;
    float speed;
};

#endif
