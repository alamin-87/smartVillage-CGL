#ifndef HUMAN_H
#define HUMAN_H

class Human {
public:
    Human(float startX, float startY);
    void update();
    void render();
    
    void setSitting(bool sitting) { isSitting = sitting; }
    bool getSitting() const { return isSitting; }

private:
    float posX, posY;
    float speed;
    float legAngle;
    float legDir;
    bool isSitting;
};

#endif
