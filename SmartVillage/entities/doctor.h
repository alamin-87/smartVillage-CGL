#ifndef DOCTOR_H
#define DOCTOR_H

class Doctor {
public:
    Doctor(float startX, float startY);
    void update();
    void render();
    void setSpeed(float s) { speed = s; }

private:
    float posX, posY;
    float speed;
    float legAngle;
    float legDir;
};

#endif
