#ifndef ROAD_H
#define ROAD_H

class Road {
public:
    Road(float x, float y, float width);
    void render();

private:
    float posX, posY, roadWidth;
};

#endif
