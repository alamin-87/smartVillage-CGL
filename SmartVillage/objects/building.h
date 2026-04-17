#ifndef BUILDING_H
#define BUILDING_H

class Building {
public:
    Building(float x, float y, int floors, float width, int type);
    void render(bool isNight);

private:
    float posX, posY;
    int numFloors;
    float bWidth;
    int bType; // 0=Office, 1=Apartment
};

#endif
