#ifndef BIRD_H
#define BIRD_H

class Bird {
public:
    Bird(float x, float y, bool isFlying = true);
    void update();
    void render();
    
    void setX(float x) { posX = x; }
    void setY(float y) { posY = y; }

private:
    float posX, posY;
    float startY;
    float wingAngle;
    float wingDir;
    bool isFlying;
    float speed;
    float flapSpeed;
    float hoverOffset;
    float hoverTime;
};

#endif
