#ifndef URBAN_SCENE_H
#define URBAN_SCENE_H
#include "scene.h"
#include "../objects/building.h"       
#include "../objects/school.h"
#include "../objects/hospital.h"
#include "../objects/road.h"
#include "../objects/traffic_light.h"
#include "../objects/cloud.h"
#include "../ui/hud.h"
#include "../entities/human.h"
#include "../entities/child.h"
#include "../smart/lighting_system.h"
#include "../effects/rain_effect.h"
#include "../effects/storm_effect.h"
#include <vector>

class UrbanScene : public Scene {
public:
    void init() override;
    void update() override;
    void render() override;
    ~UrbanScene() override;

    void toggleRain() override { isRainy = !isRainy; }
    void toggleStorm() override { isStormy = !isStormy; }
    void toggleWind() override { isWindy = !isWindy; }
    void setDayNight(bool forceNight) override { 
        if (forceNight) sunAngle = 200.0f; else sunAngle = 45.0f;
    }

private:
    float sunAngle;
    bool isNight;
    bool isRainy, isStormy, isWindy;
    
    School *school;
    Hospital *hospital;
    Building *buildings[3];
    Road *mainRoad;
    TrafficLight *trafficLight;
    
    std::vector<Human*> citizens;
    std::vector<Child*> students;
    LightingSystem *streetLights[4];
    Cloud *clouds[2];
    
    RainEffect *rain;
    StormEffect *storm;
    HUD hud;
};
#endif
