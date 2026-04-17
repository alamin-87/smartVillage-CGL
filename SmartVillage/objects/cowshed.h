#ifndef COWSHED_H
#define COWSHED_H
class CowShed {
public:
    CowShed(float x, float y);
    void render(bool gateOpen);
private:
    float posX, posY;
};
#endif
