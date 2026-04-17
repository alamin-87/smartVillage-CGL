#ifndef FOOTPATH_H
#define FOOTPATH_H

class Footpath {
public:
    Footpath(float y, float width);
    void render();

private:
    float posY, footWidth;
};

#endif
