#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {
public:
    Vehicle(float x, float y, int type, float speed);
    void update();
    void render();

private:
    float posX, posY;
    float speed;
    int type; // 0: Car, 1: Bus, 2: Hiace, 3: Motorcycle, 4: Bicycle
    float color[3];
    float wheelRotation;

    void drawCar();
    void drawBus();
    void drawHiace();
    void drawMotorcycle();
    void drawBicycle();
};

#endif
