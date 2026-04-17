#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

// Manages delta time and frame timing for consistent animation speed
class TimeManager {
public:
    static TimeManager& getInstance();

    void update();
    float getDeltaTime() const { return deltaTime; }
    float getElapsedTime() const { return elapsedTime; }
    int getFPS() const { return fps; }

private:
    TimeManager();
    float deltaTime;
    float elapsedTime;
    int fps;
    int frameCount;
    float fpsTimer;
    int lastTime;
};

#endif
