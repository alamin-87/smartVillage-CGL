#ifndef ALAMIN_H
#define ALAMIN_H

class Alamin {
public:
    Alamin(float x, float y);
    void update();
    void render();
    void setTarget(float tx);
    float getX() const { return posX; }
    
private:
    float posX, posY;
    float targetX;
    float moveTime;
    bool isWalking;
};

#endif
