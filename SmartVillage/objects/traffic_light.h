#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

class TrafficLight {
public:
    TrafficLight(float x, float y);
    void update(float dt);
    void render();

private:
    float posX, posY;
    int state; // 0=Red, 1=Yellow, 2=Green
    float timer;
};

#endif
