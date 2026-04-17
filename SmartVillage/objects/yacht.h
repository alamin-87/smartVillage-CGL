#ifndef YACHT_H
#define YACHT_H

class Yacht {
private:
    float posX, posY;
    float speed;
    float swayAngle;

public:
    Yacht(float x, float y);
    void update();
    void render(bool isNight);
};

#endif
