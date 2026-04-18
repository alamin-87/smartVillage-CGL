#ifndef CHILD_H
#define CHILD_H

class Child {
public:
    Child(float startX, float startY, int variety = 0);
    void update();
    void render();
    void setSpeed(float s) { baseSpeed = s; }
    void setPlaying(bool p) { isPlaying = p; }
    void setSitting(bool s) { isSitting = s; }
    void setBounds(float min, float max) { minX = min; maxX = max; }
    void setYBounds(float min, float max) { minY = min; maxY = max; }
    void setChildScale(float s) { childScale = s; }

private:
    void pickNewDirection();
    void renderSideView(float skinR, float skinG, float skinB);
    void renderFrontView(float skinR, float skinG, float skinB);
    void renderBackView(float skinR, float skinG, float skinB);

    float posX, posY;
    float startYBase;
    float baseSpeed;
    float legAngle;
    float jumpOffset;
    float jumpTime;
    bool isPlaying;
    float minX = -7.0f, maxX = 7.0f;
    float minY = -1.0f, maxY = 1.0f;
    float childScale;
    bool isSitting = false;
    int variety;
    float shirtR, shirtG, shirtB;
    int direction; // 0:R, 1:L, 2:F, 3:B
    int stateTimer;
};

#endif
