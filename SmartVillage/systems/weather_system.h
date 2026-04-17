#ifndef WEATHER_SYSTEM_H
#define WEATHER_SYSTEM_H

// Centralized weather state manager for the entire simulation
class WeatherSystem {
public:
    static WeatherSystem& getInstance();

    void update(float dt);

    // Toggle weather conditions
    void toggleRain();
    void toggleStorm();
    void toggleWind();

    // Getters
    bool isRaining() const { return rainy; }
    bool isStorming() const { return stormy; }
    bool isWindy() const { return windy; }
    float getWindStrength() const { return windStrength; }
    float getRainIntensity() const { return rainIntensity; }
    float getTemperature() const { return temperature; }
    const char* getStatusText() const;

private:
    WeatherSystem();
    bool rainy, stormy, windy;
    float windStrength;     // 0.0 to 1.0
    float rainIntensity;    // 0.0 to 1.0
    float temperature;      // Celsius
    float transitionTimer;
};

#endif
