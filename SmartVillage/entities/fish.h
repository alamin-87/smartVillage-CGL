#ifndef FISH_H
#define FISH_H

class Fish {
public:
    Fish(float x, float y, float r, float g, float b);
    void update();
    void render();

private:
    float posX, posY;
    float baseY;
    float speed;
    float swimTime;
    float colorR, colorG, colorB;
    bool jumping;
    float jumpTime;
};

#endif
