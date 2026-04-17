#ifndef APPLICATION_H
#define APPLICATION_H

#include "../scene/village_scene.h"
#include "../scene/rural_scene.h"
#include "../scene/urban_scene.h"
#include "../entities/alamin.h"
#include "../ui/hud.h"

class Application {
private:
    static Application* instance;

    VillageScene* village;
    RuralScene* rural;
    UrbanScene* urban;
    Alamin* alamin;
    HUD hud;

    float cameraX;
    float globalTime;
    bool isNight;
    bool isRainy, isStormy, isWindy;

    Application();

public:
    static Application& getInstance();

    void init();
    void update();
    void render();
    void handleInput(unsigned char key);

    // Getters for shared state
    void setTargetDestination(int dest);
};

#endif