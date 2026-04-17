#ifndef HOSPITAL_H
#define HOSPITAL_H
class Hospital {
public:
    Hospital(float x, float y);
    void update(float dt);
    void render(bool isNight);
private:
    float posX, posY;
    float flashTimer;
    bool flashState;
    void drawCross(float x, float y, float size);
    void drawAmbulance(float ax, float ay);
};
#endif
