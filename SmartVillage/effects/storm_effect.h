#ifndef STORM_EFFECT_H
#define STORM_EFFECT_H

class StormEffect {
public:
    StormEffect();
    void update();
    void render();
    bool isFlashing() const { return flashActive; }

private:
    int flashTimer;
    bool flashActive;
};

#endif
