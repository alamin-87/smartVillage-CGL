#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

class LightingSystem {
public:
    LightingSystem(float x, float y);
    void update(bool isNight);
    void render();

private:
    float posX, posY;
    bool lightOn;
};

#endif
