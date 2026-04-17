#ifndef ALAMIN_H
#define ALAMIN_H

class Alamin {
public:
    Alamin(float x, float y);
    void update();
    void render();
    void setTarget(float tx);
    void setX(float x) { posX = x; targetX = x; isWalking = false; }
    float getX() const { return posX; }
    
private:
    float posX, posY;
    float targetX;
    float moveTime;
    bool isWalking;
};

#endif
