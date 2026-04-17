#ifndef CHILD_H
#define CHILD_H

class Child {
public:
    Child(float startX, float startY);
    void update();
    void render();

private:
    float posX, posY;
    float speed;
    float legAngle;
    float jumpOffset;
    float jumpTime;
};

#endif
