#include "time_manager.h"
#include <GL/glut.h>

TimeManager::TimeManager() {
    deltaTime = 0.016f;
    elapsedTime = 0.0f;
    fps = 60;
    frameCount = 0;
    fpsTimer = 0.0f;
    lastTime = 0;
}

TimeManager& TimeManager::getInstance() {
    static TimeManager instance;
    return instance;
}

void TimeManager::update() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (lastTime == 0) lastTime = currentTime;

    deltaTime = (currentTime - lastTime) / 1000.0f;
    if (deltaTime > 0.1f) deltaTime = 0.016f; // cap large jumps
    
    lastTime = currentTime;
    elapsedTime += deltaTime;

    // FPS calculation
    frameCount++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0f) {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = 0.0f;
    }
}
