#ifndef ANIMAL_H
#define ANIMAL_H

class Animal {
public:
    Animal(float startX, float startY);
    void update();
    void render();

private:
    float posX, posY;
    float speed;
    float tailAngle;
    float moveTime;
};

#endif
