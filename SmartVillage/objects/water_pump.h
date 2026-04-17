#ifndef WATER_PUMP_H
#define WATER_PUMP_H

class WaterPump {
public:
    WaterPump(float x, float y);
    void update(bool isActive);
    void render();

private:
    float posX, posY;
    float handleAngle;
    float waterLevel;
    bool pumping;
};

#endif
