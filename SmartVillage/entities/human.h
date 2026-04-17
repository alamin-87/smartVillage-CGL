#ifndef HUMAN_H
#define HUMAN_H

class Human {
public:
    Human(float startX, float startY);
    void update();
    void render();
    
    void setSitting(bool sitting) { isSitting = sitting; }
    bool getSitting() const { return isSitting; }
    void setSpeed(float s) { speed = s; }
    void setBounds(float min, float max) { minX = min; maxX = max; }

private:
    float posX, posY;
    float speed;
    float legAngle;
    float legDir;
    bool isSitting;
    float minX = -1.0f, maxX = 1.0f;
};

#endif
