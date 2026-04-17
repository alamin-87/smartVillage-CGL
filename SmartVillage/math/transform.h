#ifndef TRANSFORM_H
#define TRANSFORM_H

// 2D Transform helper for positioning and scaling objects
struct Transform2D {
    float x, y;
    float scaleX, scaleY;
    float rotation; // degrees

    Transform2D();
    Transform2D(float x, float y);
    Transform2D(float x, float y, float scale);

    // Apply this transform using OpenGL matrix operations
    void apply() const;

    // Undo this transform (call after rendering)
    void unapply() const;

    // Calculate distance to another transform
    float distanceTo(const Transform2D& other) const;

    // Move toward a target position with given speed
    void moveToward(float targetX, float targetY, float speed);
};

#endif
