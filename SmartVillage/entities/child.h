#ifndef CHILD_H
#define CHILD_H

class Child {
public:
    Child(float startX, float startY);
    void update();
    void render();
    void setSpeed(float s) { speed = s; }
    void setPlaying(bool p) { isPlaying = p; }
    void setSitting(bool s) { isSitting = s; }
    void setBounds(float min, float max) { minX = min; maxX = max; }
    void setChildScale(float s) { childScale = s; }

private:
    float posX, posY;
    float speed;
    float legAngle;
    float jumpOffset;
    float jumpTime;
    bool isPlaying;
    float minX = -1.2f, maxX = 1.2f;
    float childScale;
    bool isSitting = false;
};

#endif
