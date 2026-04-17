#ifndef WIND_EFFECT_H
#define WIND_EFFECT_H

// Visible wind particle streaks blowing across the scene
class WindEffect {
public:
    WindEffect();
    void update(float strength);
    void render();

private:
    struct WindParticle {
        float x, y;
        float length;
        float speed;
    };
    static const int NUM_PARTICLES = 30;
    WindParticle particles[NUM_PARTICLES];
};

#endif
