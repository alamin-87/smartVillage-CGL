#ifndef HOUSE_H
#define HOUSE_H

class House {
public:
    House(float x, float y);

    void render(bool isNight);

private:
    float posX, posY;
};

#endif