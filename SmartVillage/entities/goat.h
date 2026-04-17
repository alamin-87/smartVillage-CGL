#ifndef GOAT_H
#define GOAT_H
class Goat {
public:
    Goat(float x, float y);
    void update();
    void render();
private:
    float posX, posY, baseY;
    float moveTime, hopTimer, eatingTimer;
    bool hopping, eating;
};
#endif
