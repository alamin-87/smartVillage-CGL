#ifndef HEN_H
#define HEN_H
class Hen {
public:
    Hen(float x, float y);
    void update();
    void render();
private:
    float posX, posY;
    float peckTime;
    float moveTime;
    bool pecking;
};
#endif
