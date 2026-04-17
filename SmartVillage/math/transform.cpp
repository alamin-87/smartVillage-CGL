#include "transform.h"
#include <GL/glut.h>
#include <cmath>

Transform2D::Transform2D() : x(0), y(0), scaleX(1), scaleY(1), rotation(0) {}

Transform2D::Transform2D(float x, float y) : x(x), y(y), scaleX(1), scaleY(1), rotation(0) {}

Transform2D::Transform2D(float x, float y, float scale) 
    : x(x), y(y), scaleX(scale), scaleY(scale), rotation(0) {}

void Transform2D::apply() const {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    if (rotation != 0.0f) glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    if (scaleX != 1.0f || scaleY != 1.0f) glScalef(scaleX, scaleY, 1.0f);
}

void Transform2D::unapply() const {
    glPopMatrix();
}

float Transform2D::distanceTo(const Transform2D& other) const {
    float dx = other.x - x;
    float dy = other.y - y;
    return sqrtf(dx * dx + dy * dy);
}

void Transform2D::moveToward(float targetX, float targetY, float speed) {
    float dx = targetX - x;
    float dy = targetY - y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist > 0.001f) {
        x += (dx / dist) * speed;
        y += (dy / dist) * speed;
    }
}
