#ifndef RAIN_EFFECT_H
#define RAIN_EFFECT_H

class RainEffect {
public:
    RainEffect();
    void update();
    void render();

private:
    struct Drop {
        float x, y, length, speed;
    };
    static const int NUM_DROPS = 100;
    Drop drops[NUM_DROPS];
};

#endif
