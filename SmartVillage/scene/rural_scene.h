#ifndef RURAL_SCENE_H
#define RURAL_SCENE_H
#include "scene.h"
#include <vector>
#include "../objects/tree.h"
#include "../objects/house.h"       
#include "../objects/cowshed.h"
#include "../objects/water_pump.h"
#include "../objects/pole.h"
#include "../objects/cloud.h"
#include "../entities/human.h"
#include "../entities/child.h"
#include "../entities/cow.h"
#include "../entities/goat.h"
#include "../entities/duck.h"
#include "../entities/hen.h"
#include "../entities/bird.h"
#include "../ui/hud.h"
#include "../effects/rain_effect.h"
#include "../effects/storm_effect.h"

class RuralScene : public Scene {
public:
    void init() override;
    void update() override;
    void render() override;
    ~RuralScene() override;

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
    
    Tree *trees[5];
    House *familyHouse;
    CowShed *shed;
    WaterPump *pump;
    Pole *pole;
    Cloud *clouds[3];
    std::vector<Bird*> birds;

    Human *father;
    Human *mother;
    Child *child1;
    Child *child2;
    Child *child3;
    Child *child4;
    Child *child5;
    
    std::vector<Child*> distantChildren;

    Cow *cow;
    Goat *goat;
    Duck *duck;
    Hen *hen;

    RainEffect *rain;
    StormEffect *storm;
    HUD hud;
    
    void drawFields();
    void drawPond();
    void drawRealisticHouses(float x, float y);
    void drawBushyTree(float x, float y);
    void drawPalmTree(float x, float y);
    void drawWoodenFence(float x, float y);
    void drawMangoTree(float x, float y);
    void drawSmallHouse(float x, float y);
    void drawChildPark(float x, float y);
};
#endif
