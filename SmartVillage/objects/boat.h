#ifndef BOAT_H
#define BOAT_H

class Boat {
public:
    Boat(float x, float y);
    void update();
    void render(bool isNight);

    void setBounds(float min, float max) { minX = min; maxX = max; }

private:
    float posX, posY;
    float swayAngle;
    float speed;
    float minX = -1.3f, maxX = 1.3f;
    void drawFisherman();
};

#endif
