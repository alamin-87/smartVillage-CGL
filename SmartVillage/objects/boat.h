#ifndef BOAT_H
#define BOAT_H

class Boat {
public:
    Boat(float x, float y);
    void update();
    void render(bool isNight);

private:
    float posX, posY;
    float swayAngle;
    float speed;
    void drawFisherman();
};

#endif
