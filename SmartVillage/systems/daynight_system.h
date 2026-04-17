#ifndef DAYNIGHT_SYSTEM_H
#define DAYNIGHT_SYSTEM_H

// Manages the day/night cycle with smooth sky color transitions
class DayNightSystem {
public:
    static DayNightSystem& getInstance();

    void update(float dt);
    void forceDay();
    void forceNight();

    // Getters
    float getSunAngle() const { return sunAngle; }
    bool isNight() const { return night; }
    bool isDusk() const;
    bool isDawn() const;
    int getHour() const;
    float getDayProgress() const; // 0.0 = midnight, 0.5 = noon, 1.0 = midnight

    // Sky colors for current time
    void getSkyColor(float& r, float& g, float& b) const;
    
    // Ambient light intensity (0.0 = dark, 1.0 = bright)
    float getAmbientIntensity() const;

private:
    DayNightSystem();
    float sunAngle;
    bool night;
    float cycleSpeed;
};

#endif
