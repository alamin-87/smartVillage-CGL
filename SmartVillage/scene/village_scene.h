#ifndef VILLAGE_SCENE_H
#define VILLAGE_SCENE_H
#include "scene.h"
#include "../objects/tree.h"
#include "../objects/house.h"       
#include "../objects/river.h"
#include "../objects/market.h"
#include "../objects/boat.h"
#include "../effects/rain_effect.h"
#include "../effects/storm_effect.h"
#include "../smart/lighting_system.h"
#include "../entities/human.h"
#include "../entities/child.h"
#include "../entities/fish.h"
#include "../objects/cloud.h"
#include "../objects/road.h"
#include "../ui/hud.h"
#include <vector>

class VillageScene : public Scene {
public:
    void init() override;
    void update() override;
    void render() override;
    ~VillageScene() override;

    void toggleRain() override { isRainy = !isRainy; }
    void toggleStorm() override { isStormy = !isStormy; }
    void toggleWind() override { isWindy = !isWindy; }
    void setDayNight(bool forceNight) override { 
        if (forceNight) sunAngle = 200.0f; else sunAngle = 45.0f;
    }

private:
    void drawSky();
    void drawGround();
    void drawSun();
    float sunAngle; 
    void drawMoon();
    void drawStars();

    float skyR, skyG, skyB;
    bool isNight;

    std::vector<Tree*> trees;
    River river;
    Market *market;
    Boat *boats[2];

    RainEffect *rain;
    StormEffect *storm;
    LightingSystem *streetLights[2];
    
    std::vector<Human*> villagers;
    std::vector<Human*> shopkeepers;
    std::vector<Child*> children;
    std::vector<Fish*> schoolOfFish;
    
    Cloud *clouds[3];
    HUD hud;

    bool isRainy, isStormy, isWindy;
    
    // New drawing routines for realistic Scene 1
    void drawRealisticVillageHouses(float x, float y);
    void drawSmallHouse(float x, float y);
    void drawHouseBoundary(float x, float y, float width);
    void drawVillagePath();
    void drawDetailedGrass(float x, float y);
    void drawMangoTree(float x, float y);
    void drawCoconutTree(float x, float y);
    void drawJackfruitTree(float x, float y);
    void drawMarketShop(float x, float y, float r, float g, float b);
};
#endif