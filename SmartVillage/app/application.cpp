#include "application.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>

Application* Application::instance = nullptr;

Application::Application() {
    village = nullptr;
    rural = nullptr;
    urban = nullptr;
    alamin = nullptr;
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

    // Start Alamin in the center of the village
    alamin = new Alamin(0.0f, -0.65f);

    std::cout << "Continuous World Application Initialized. Alamin is ready!" << std::endl;
}

void Application::setTargetDestination(int dest) {
    if (dest == 1) alamin->setTarget(0.0f);        // Village Center
    else if (dest == 2) alamin->setTarget(2.0f);   // Friend's Rural House (Scene 2 is at X=2.0)
    else if (dest == 3) alamin->setTarget(4.0f);   // School in Urban District (Scene 3 is at X=4.0)
}

void Application::update() {
    // Alamin Movement
    alamin->update();

    // Smooth Camera Follow
    float diff = alamin->getX() - cameraX;
    cameraX += diff * 0.05f; // Smooth interpolation

    // Sync global time across all scenes
    globalTime += 0.2f;
    if (globalTime > 360.0f) globalTime = 0.0f;
    isNight = (globalTime > 180.0f);

    // Sync weather and time to scenes implicitly through their own update loops
    village->update();
    rural->update();
    urban->update();
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

    // 2. Apply Camera Offset
    glPushMatrix();
    glTranslatef(-cameraX, 0.0f, 0.0f);

    // 3. Draw Scene 1 (Village) at X = 0.0
    glPushMatrix();
    village->render();
    glPopMatrix();

    // 4. Draw Scene 2 (Rural) at X = 2.0
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    rural->render();
    glPopMatrix();

    // 5. Draw Scene 3 (Urban) at X = 4.0
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f);
    urban->render();
    glPopMatrix();

    // 6. Draw Alamin (he exists in the global unified world coordinate space)
    alamin->render();

    glPopMatrix(); // End Camera Offset

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
            village->toggleRain(); rural->toggleRain(); urban->toggleRain(); break;
        case 's': 
            village->toggleStorm(); rural->toggleStorm(); urban->toggleStorm(); break;
        case 'w': 
            village->toggleWind(); rural->toggleWind(); urban->toggleWind(); break;
            
        case 27: exit(0); break; // ESC to quit
    }
}