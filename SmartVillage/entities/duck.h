#ifndef DUCK_H
#define DUCK_H
class Duck {
public:
    Duck(float x, float y);
    void update();
    void render();
private:
    float posX, posY;
    float waddleTime;
    float swimOffset;
    bool swimming;
};
#endif
