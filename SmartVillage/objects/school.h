#ifndef SCHOOL_H
#define SCHOOL_H
class School {
public:
    School(float x, float y);
    void update(float hour);
    void render(bool isNight);
private:
    float posX, posY;
    float flagWave;
    bool bellRinging;
    void drawFlag();
    void drawField();
};
#endif
