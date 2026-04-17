#ifndef FOOTBRIDGE_H
#define FOOTBRIDGE_H

class Footbridge {
public:
    Footbridge(float x, float y, float length);
    void render();

private:
    float posX, posY, bridgeLength;
};

#endif
