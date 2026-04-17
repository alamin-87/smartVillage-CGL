#ifndef COW_H
#define COW_H

class Cow {
public:
    Cow(float x, float y);
    void update(bool isNight);
    void render();
private:
    float posX, posY;
    float baseX;
    float moveTime;
    float tailSwing;
    float headBob;
    bool inShed;
};

#endif
