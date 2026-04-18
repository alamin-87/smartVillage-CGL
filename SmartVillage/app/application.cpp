#include "application.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "../smart/energy_system.h"
#include "../smart/building_system.h"
#include "../systems/sound_manager.h"

Application* Application::instance = nullptr;

Application::Application() {
    village = nullptr;
    rural = nullptr;
    urban = nullptr;
    alamin = nullptr;
    currentSceneId = 1; // Default to Village
    cameraX = 0.0f;
    globalTime = 45.0f; // Start at morning
}

Application& Application::getInstance() {
    if (instance == nullptr) {
        instance = new Application();
    }
    return *instance;
}

void Application::init() {
    village = new VillageScene();
    rural = new RuralScene();
    urban = new UrbanScene();
    
    village->init();
    rural->init();
    urban->init();

    // Start Alamin on the road center
    alamin = new Alamin(0.0f, -0.55f);

    std::cout << "Separated Scene Application Initialized. Alamin is ready!" << std::endl;
}

void Application::setTargetDestination(int dest) {
    currentSceneId = dest;
    alamin->setX(0.0f); // Reset Alamin to center of the specific scene
    cameraX = 0.0f;     // Reset camera for the new scene
}

void Application::update() {
    // Alamin Movement
    alamin->update();

    // Scene-specific limits
    float sceneBound = (currentSceneId == 1) ? 6.8f : 0.95f;
    float camBound = (currentSceneId == 1) ? 5.8f : 0.0f;

    // Clamp Alamin to scene
    if (alamin->getX() > sceneBound) alamin->setX(sceneBound);
    if (alamin->getX() < -sceneBound) alamin->setX(-sceneBound);

    // Smooth Camera Follow with per-scene clamping
    float targetCamX = alamin->getX();
    if (targetCamX > camBound) targetCamX = camBound;
    if (targetCamX < -camBound) targetCamX = -camBound;
    
    float diff = targetCamX - cameraX;
    cameraX += diff * 0.05f;

    // Sync global time
    globalTime += 0.2f;
    if (globalTime > 360.0f) globalTime = 0.0f;
    isNight = (globalTime > 180.0f);

    // Update ONLY the active scene
    if (currentSceneId == 1) village->update();
    else if (currentSceneId == 2) rural->update();
    else if (currentSceneId == 3) urban->update();

    // Update smart systems
    int activeLights = isNight ? 6 : 0;
    int activeBuildings = 6;
    float outsideTemp = isNight ? 24.0f : 32.0f;
    if (isRainy) outsideTemp -= 5.0f;
    if (isStormy) outsideTemp -= 8.0f;

    EnergySystem::getInstance().update(0.016f, isNight, isStormy, activeLights, activeBuildings);
    BuildingSystem::getInstance().update(0.016f, isNight, outsideTemp);
}

void Application::render() {
    // 1. Draw Global Unified Sky
    float intensity = sin(globalTime * 3.14159f / 180.0f);
    float bgR = 0.4f, bgG = 0.6f, bgB = 0.8f;
    if (intensity > 0) {
        bgR = 0.4f + (0.1f * (1.0f - intensity));
        bgG = 0.6f + (0.2f * intensity);
        bgB = 0.8f + (0.2f * intensity);
    } else {
        float nightFactor = -intensity;
        bgR = 0.05f * (1.0f - nightFactor);
        bgG = 0.05f * (1.0f - nightFactor);
        bgB = 0.15f + (0.05f * (1.0f - nightFactor));
    }
    glClearColor(bgR, bgG, bgB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // celestial bodies stay in screen space
    if (globalTime < 180.0f) {
        // Draw Sun (simplified, let village/rural/urban do their own if they want, 
        // but it's better here for consistency)
    }

    // 2. Camera Offset (Selective for active scene)
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f);
    
    // 3. Render only the CURRENT active scene
    if (currentSceneId == 1) {
        village->render();
    } else if (currentSceneId == 2) {
        rural->render();
    } else if (currentSceneId == 3) {
        urban->render();
    }

    glPopMatrix(); 

    // 7. Draw HUD in screen space
    hud.render(globalTime, isRainy, isStormy, isWindy);

    glutSwapBuffers();
}

void Application::handleInput(unsigned char key) {
    if (!alamin) return;

    switch (key) {
        // Alamin Movement Controls
        case '1': setTargetDestination(1); break; // Go to Village
        case '2': setTargetDestination(2); break; // Go to Rural
        case '3': setTargetDestination(3); break; // Go to School

        // Weather Controls (Applies globally)
        case 'd': 
            village->setDayNight(false); rural->setDayNight(false); urban->setDayNight(false); 
            globalTime = 45.0f; break;
        case 'n': 
            village->setDayNight(true); rural->setDayNight(true); urban->setDayNight(true); 
            globalTime = 200.0f; break;
        case 'r': 
            isRainy = !isRainy;
            village->toggleRain(); rural->toggleRain(); urban->toggleRain(); 
            if (isRainy) SoundManager::getInstance().playRain();
            else SoundManager::getInstance().stopRain();
            break;
        case 's': 
            isStormy = !isStormy;
            village->toggleStorm(); rural->toggleStorm(); urban->toggleStorm(); 
            if (isStormy) SoundManager::getInstance().playStorm();
            else SoundManager::getInstance().stopStorm();
            break;
        case 'w': 
            isWindy = !isWindy;
            village->toggleWind(); rural->toggleWind(); urban->toggleWind(); 
            if (isWindy) SoundManager::getInstance().playWind();
            else SoundManager::getInstance().stopWind();
            break;
            
        case 'c': 
            if (SoundManager::getInstance().isChildPlaying()) SoundManager::getInstance().stopChild();
            else SoundManager::getInstance().playChild();
            break;
        case 27: exit(0); break; // ESC to quit
    }
}