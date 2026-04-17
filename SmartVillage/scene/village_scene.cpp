#include "village_scene.h"
#include "../app/application.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

struct Prop {
    float x, y;
    int type;
};

std::vector<Prop> smallHouses;
std::vector<Prop> shopLocations;

void VillageScene::init() {
    sunAngle = 45.0f;
    isNight = false;
    isRainy = isStormy = isWindy = false;

    // Background Trees on the field edge (y=0.15 to 0.2)
    for (float x = -6.5f; x < 1.5f; x += 0.8f) {
        trees.push_back(new Tree(x, 0.1f));
    }

    // Small Houses on Field (strictly below river horizon y=0.2)
    for (int i = 0; i < 20; i++) {
        float hx = (rand() % 1300 - 650) / 100.0f;
        float hy = (rand() % 10 + 2) / 100.0f; // y is 0.02 to 0.12
        smallHouses.push_back({hx, hy, rand() % 3});
    }

    // Market Shops near road (foreground)
    for (int i = 0; i < 12; i++) {
        float sx = -5.5f + (i * 1.0f);
        shopLocations.push_back({sx, -0.8f, i % 7});
        Human* vendor = new Human(sx, -0.8f);
        vendor->setSitting(true);
        shopkeepers.push_back(vendor);
    }

    // Boats on River (within visible range)
    boats[0] = new Boat(-0.5f, 0.3f);
    boats[1] = new Boat( 0.6f, 0.35f);
    yacht = new Yacht(-1.2f, 0.25f);

    rain = new RainEffect();
    storm = new StormEffect();
    
    // People walking ON THE ROAD
    for(int i=0; i<3; i++) {
        villagers.push_back(new Human(-5.0f + i*5.0f, -0.52f));
    }
    children.push_back(new Child(1.0f, -0.55f)); 
    children.push_back(new Child(-2.0f, -0.48f));

    // Children exactly positioned on park equipment: Left Swing, Right Swing, Seesaw Left, Seesaw Right, Slide Platform (Adjusted for smaller scale)
    float parkKids[][2] = {{-0.72f, -0.24f}, {-0.64f, -0.24f}, {-0.575f, -0.28f}, {-0.465f, -0.28f}, {-0.28f, -0.145f}};
    for(int i = 0; i < 5; i++) {
        Child* kid = new Child(parkKids[i][0], parkKids[i][1]);
        kid->setSpeed(0.0f);
        kid->setPlaying(true);
        kid->setChildScale(0.45f); // Make park children smaller to fit the park
        parkChildren.push_back(kid);
    }

    // Children playing in the far distance
    Child* dc1 = new Child(1.2f, 0.05f); dc1->setChildScale(0.25f); dc1->setSpeed(0.0f); dc1->setPlaying(true);
    Child* dc2 = new Child(1.4f, 0.05f); dc2->setChildScale(0.25f); dc2->setSpeed(0.0f); dc2->setPlaying(true);
    Child* dc3 = new Child(-3.2f, 0.1f); dc3->setChildScale(0.2f); dc3->setSpeed(0.0f); dc3->setPlaying(true);
    distantChildren.push_back(dc1);
    distantChildren.push_back(dc2);
    distantChildren.push_back(dc3);

    // 5 children sitting in a circle beside the river (moved further right)
    // Center around X = 4.8f, Y = 0.16f
    Child* rc1 = new Child(4.8f, 0.18f); rc1->setChildScale(0.3f); rc1->setSitting(true);
    Child* rc2 = new Child(4.72f, 0.16f); rc2->setChildScale(0.3f); rc2->setSitting(true);
    Child* rc3 = new Child(4.88f, 0.16f); rc3->setChildScale(0.3f); rc3->setSitting(true);
    Child* rc4 = new Child(4.75f, 0.14f); rc4->setChildScale(0.3f); rc4->setSitting(true);
    Child* rc5 = new Child(4.85f, 0.14f); rc5->setChildScale(0.3f); rc5->setSitting(true);
    distantChildren.push_back(rc1);
    distantChildren.push_back(rc2);
    distantChildren.push_back(rc3);
    distantChildren.push_back(rc4);
    distantChildren.push_back(rc5);

    // Farm Animals (goats, hens) scattered in the field areas
    // One goat in the free green space right behind the park
    goats.push_back(new Goat(-0.45f, -0.10f));
    goats.push_back(new Goat(0.9f, -0.15f));
    
    hens.push_back(new Hen(0.2f, -0.15f));
    hens.push_back(new Hen(0.3f, -0.18f));
    hens.push_back(new Hen(-1.0f, -0.20f));
    hens.push_back(new Hen(-1.05f, -0.22f));
    hens.push_back(new Hen(1.1f, -0.12f));

    // Fish INSIDE RIVER (y = 0.22 to 0.38)
    for (int i=0; i<10; i++) {
        schoolOfFish.push_back(new Fish(-5.5f + i*1.2f, 0.3f, 0.9f, 0.6f, 0.2f));
    }

    clouds[0] = new Cloud(-4.5f, 0.7f, 1.2f);
    clouds[1] = new Cloud(-1.0f, 0.8f, 0.9f);
    clouds[2] = new Cloud( 3.0f, 0.6f, 1.1f);
    for(int i=0; i<3; i++) clouds[i]->setBounds(-7.5f, 7.5f);

    // Initialize stars once
    for (int i = 0; i < 100; i++) {
        stars.push_back({
            (rand() % 1400 - 700) / 100.0f, // Wider star field for village
            (rand() % 45 + 45) / 100.0f,
            (rand() % 20 + 10) / 10.0f, // size
            (float)(rand() % 360)     // phase
        });
    }

    // Set boundaries for other interactive entities in scene
    for(auto v : villagers) v->setBounds(-7.0f, 7.0f);
    for(auto c : children) c->setBounds(-7.0f, 7.0f);
    for(int i=0; i<2; i++) boats[i]->setBounds(-7.0f, 7.0f);
}

VillageScene::~VillageScene() {
    for(auto t : trees) delete t;
    for(int i=0; i<2; i++) delete boats[i];
    delete yacht;
    delete rain; delete storm;
    for(auto v : villagers) delete v;
    for(auto s : shopkeepers) delete s;
    for(auto c : children) delete c;
    for(auto pk : parkChildren) delete pk;
    for(auto dc : distantChildren) delete dc;
    for(auto f : schoolOfFish) delete f;
    for(auto g : goats) delete g;
    for(auto h : hens) delete h;
    for(int i=0; i<3; i++) delete clouds[i];
}

void VillageScene::update() {
    sunAngle += 0.08f;
    if (sunAngle > 360.0f) sunAngle = 0.0f;
    isNight = (sunAngle > 180.0f);

    for(auto t : trees) t->update(isWindy);
    for(int i=0; i<2; i++) boats[i]->update();
    yacht->update();
    
    if (isRainy || isStormy) rain->update();
    if (isStormy) storm->update();
    
    for(auto v : villagers) v->update();
    for(auto c : children) c->update();
    for(auto pk : parkChildren) pk->update();
    for(auto dc : distantChildren) dc->update();
    for(auto f : schoolOfFish) f->update();
    for(auto g : goats) g->update();
    for(auto h : hens) h->update();
    
    river.update();
    for(int i=0; i<3; i++) clouds[i]->update(isWindy, isStormy);
}

void VillageScene::render() {
    // Ground Field (y = -1.0 to 0.2)
    drawGround();
    
    if (!isNight) drawSun();
    else { drawMoon(); drawStars(); }
    
    if (isStormy) storm->render();

    for(int i=0; i<3; i++) clouds[i]->render();
    
    // 2. The Upgraded River (Horizon background, y = 0.2 to 0.45)
    glBegin(GL_QUADS);
        // Gradient for depth
        if(!isNight) glColor3f(0.0f, 0.6f, 1.0f); else glColor3f(0.0f, 0.1f, 0.4f);
        glVertex2f(-7.0f, 0.45f); glVertex2f(7.0f, 0.45f);
        if(!isNight) glColor3f(0.0f, 0.3f, 0.7f); else glColor3f(0.0f, 0.05f, 0.25f);
        glVertex2f(7.0f, 0.20f);  glVertex2f(-7.0f, 0.20f);
    glEnd();
    
    // Dynamic Flowing Ripple Layers
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (float rx = -7.0f; rx < 7.0f; rx += 0.3f) {
        // Layer 1 (Fast, white glints)
        float x1 = rx + sin(sunAngle*0.1f + rx) * 0.1f;
        glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
        drawBresenhamLine(x1, 0.35f, x1 + 0.12f, 0.35f);
        
        // Layer 2 (Slower, dark ripples)
        float x2 = rx - cos(sunAngle*0.05f + rx) * 0.15f;
        glColor4f(0.0f, 0.2f, 0.5f, 0.4f);
        drawBresenhamLine(x2, 0.4f, x2 + 0.2f, 0.4f);

        // Sunlight Glimmer Points
        if (!isNight) {
            glColor4f(0.8f, 0.95f, 1.0f, 0.5f);
            glBegin(GL_POINTS);
                glVertex2f(rx + sin(sunAngle*0.2f)*0.5f, 0.25f + (rand()%10)/100.0f);
            glEnd();
        }
    }
    glDisable(GL_BLEND);
    
    for(int i=0; i<2; i++) boats[i]->render(isNight);
    yacht->render(isNight);
    for(auto f : schoolOfFish) f->render();

    // Environment and Houses only on the field (y < 0.2)
    for(auto t : trees) t->render();
    for(auto& h : smallHouses) drawSmallHouse(h.x, h.y);
    
    // Render distant background children before main houses so they appear far away
    for(auto dc : distantChildren) dc->render();
    
    // Positioned to the left and scaled down 
    glPushMatrix();
    glTranslatef(-0.35f, 0.05f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f); 
    drawMangoTree(0.0f, 0.0f);
    glPopMatrix();

    // NEW: Positioned further to the right and slightly forward
    glPushMatrix();
    glTranslatef(0.85f, -0.1f, 0.0f);
    glScalef(0.65f, 0.65f, 1.0f); 
    drawMangoTree(0.0f, 0.0f);
    glPopMatrix();
    
    float housePositions[] = {-5.0f, -3.8f, -2.4f, -1.1f, 0.4f, 1.8f, 3.0f, 4.3f};
    int treeTypes[] = {0, 1, 2, 0, 1, 0, 2, 1};
    for (int i = 0; i < 8; i++) {
        float hX = housePositions[i];
        float hY = -0.1f + (i % 2 == 0 ? 0.03f : -0.03f); 
        drawRealisticVillageHouses(hX, hY);
        drawHouseBoundary(hX, hY - 0.05f, 0.6f);
        if (treeTypes[i] == 0) drawMangoTree(hX + 0.22f, hY);
        else if (treeTypes[i] == 1) drawCoconutTree(hX + 0.22f, hY);
        else drawJackfruitTree(hX + 0.22f, hY);
    }
    
    drawVillagePath();

    // Farm animals rendered before people
    for(auto g : goats) g->render();
    for(auto h : hens) h->render();

    // Child Park in the middle free space (shifted slightly right)
    drawChildPark(-0.50f, -0.25f);
    for(auto pk : parkChildren) pk->render();

    // 5. ROAD PEOPLE (Rendered before market for perspective)
    for(auto v : villagers) v->render();
    for(auto c : children) c->render();
    
    // 6. ALAMIN (The Main Character)
    Application::getInstance().getAlamin()->render();

    // 7. MARKET (Rendered LAST so it's in the foreground)
    float stallColors[][3] = {{0.9f, 0.1f, 0.1f}, {0.1f, 0.8f, 0.2f}, {0.1f, 0.2f, 0.9f}, {0.9f, 0.8f, 0.1f}, {0.7f, 0.1f, 0.7f}, {0.9f, 0.5f, 0.1f}, {0.1f, 0.8f, 0.8f}};
    for(int i = 0; i < (int)shopLocations.size(); i++) {
        Prop& p = shopLocations[i];
        shopkeepers[i]->render();
        drawMarketShop(p.x, p.y, stallColors[p.type][0], stallColors[p.type][1], stallColors[p.type][2]);
    }

    if (isRainy || isStormy) rain->render();
}

void VillageScene::drawGround() {
    glBegin(GL_QUADS);
    if(!isNight) glColor3f(0.2f, 0.8f, 0.2f); else glColor3f(0.1f, 0.3f, 0.1f);
    glVertex2f(-7.0f, 0.20f); glVertex2f( 7.0f, 0.20f);
    if(!isNight) glColor3f(0.15f, 0.6f, 0.15f); else glColor3f(0.05f, 0.2f, 0.05f);
    glVertex2f( 7.0f,-1.0f); glVertex2f(-7.0f,-1.0f);
    glEnd();
}

void VillageScene::drawVillagePath() {
    glColor3f(0.85f, 0.75f, 0.5f);
    glBegin(GL_QUAD_STRIP);
    for (float px = -7.0f; px <= 7.0f; px += 0.5f) {
        float wave = sin(px * 10.0f) * 0.04f;
        glVertex2f(px, -0.4f + wave); glVertex2f(px, -0.65f + wave);
    }
    glEnd();
    for (float x = -7.0f; x < 7.0f; x += 0.3f) {
        drawDetailedGrass(x, -0.38f + sin(x*10.0f)*0.04f); 
        drawDetailedGrass(x + 0.05f, -0.7f + sin(x*10.0f)*0.04f);
    }
}

void VillageScene::drawDetailedGrass(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor3f(0.1f, 0.5f, 0.1f); glBegin(GL_TRIANGLES);
    glVertex2f(-0.015f, 0.0f); glVertex2f(0.0f, 0.04f); glVertex2f(0.015f, 0.0f);
    glEnd(); glPopMatrix();
}

void VillageScene::drawSmallHouse(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); glScalef(0.6f, 0.6f, 1.0f);
    glColor3f(0.95f, 0.9f, 0.85f); glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.0f); glVertex2f(0.1f, 0.0f); glVertex2f(0.1f, 0.1f); glVertex2f(-0.1f, 0.1f);
    glEnd(); glColor3f(0.8f, 0.2f, 0.1f); glBegin(GL_TRIANGLES);
    glVertex2f(-0.12f, 0.1f); glVertex2f(0.12f, 0.1f); glVertex2f(0.0f, 0.18f);
    glEnd(); 
    // Small house window
    glColor3f(0.6f, 0.8f, 1.0f); glRectf(-0.04f, 0.04f, 0.04f, 0.08f);
    glPopMatrix();
}

void VillageScene::drawHouseBoundary(float x, float y, float width) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); glColor3f(0.4f, 0.25f, 0.1f);
    float hw = width/2; drawBresenhamLine(-hw, 0.02f, hw, 0.02f); drawBresenhamLine(-hw, 0.06f, hw, 0.06f);
    for (float px = -hw; px <= hw; px += 0.1f) {
        if (px > -0.05f && px < 0.05f) continue; // Boundary Door (Gate)
        glBegin(GL_QUADS); glVertex2f(px-0.005f, 0.0f); glVertex2f(px+0.005f, 0.0f); glVertex2f(px+0.005f, 0.12f); glVertex2f(px-0.005f, 0.12f); glEnd();
    }
    glPopMatrix();
}

void VillageScene::drawRealisticVillageHouses(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); float w = 0.35f; float h = 0.25f;
    glColor3f(1.0f, 0.95f, 0.85f); glBegin(GL_QUADS);
    glVertex2f(-w/2, 0.0f); glVertex2f( w/2, 0.0f); glVertex2f( w/2, h); glVertex2f(-w/2, h);
    glEnd(); glColor3f(0.9f, 0.2f, 0.1f); glBegin(GL_TRIANGLES);
    glVertex2f(-w/2-0.06f, h); glVertex2f(w/2+0.06f, h); glVertex2f(0.0f, h+0.16f);
    glEnd(); glColor3f(0.2f, 0.1f, 0.05f); glBegin(GL_QUADS);
    glVertex2f(-0.04f, 0.0f); glVertex2f(0.04f, 0.0f); glVertex2f(0.04f, 0.12f); glVertex2f(-0.04f, 0.12f);
    glEnd();
    // House Windows
    glColor3f(0.6f, 0.8f, 0.9f); glRectf(-0.13f, 0.12f, -0.08f, 0.18f); glRectf(0.08f, 0.12f, 0.13f, 0.18f);
    glPopMatrix();
}

void VillageScene::drawMarketShop(float x, float y, float r, float g, float b) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor3f(0.5f, 0.35f, 0.1f); glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.0f); glVertex2f(0.1f, 0.0f); glVertex2f(0.1f, 0.08f); glVertex2f(-0.1f, 0.08f);
    glEnd(); glColor3f(r, g, b); glBegin(GL_POLYGON);
    glVertex2f(-0.12f, 0.20f); glVertex2f(0.12f, 0.20f); glVertex2f(0.08f, 0.25f); glVertex2f(-0.08f, 0.25f);
    glEnd(); glColor3f(0.3f, 0.2f, 0.1f);
    drawBresenhamLine(-0.09f, 0.08f, -0.11f, 0.20f); drawBresenhamLine(0.09f, 0.08f, 0.11f, 0.20f);
    glPopMatrix();
}

void VillageScene::drawMangoTree(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    
    // 🪵 Realistic Thick Trunk
    glColor3f(0.35f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f); glVertex2f(0.04f, 0.0f);
        glVertex2f(0.035f, 0.1f);  glVertex2f(0.02f, 0.22f);
        glVertex2f(-0.02f, 0.22f); glVertex2f(-0.035f, 0.1f);
    glEnd();
    // Bark detail
    glColor3f(0.25f, 0.15f, 0.05f);
    drawBresenhamLine(-0.01f, 0.02f, -0.01f, 0.15f);
    drawBresenhamLine(0.015f, 0.05f, 0.015f, 0.18f);

    // 🌳 Dense, Bushy Canopy
    glColor3f(0.05f, 0.3f, 0.05f); 
    fillMidpointCircle(0.0f,   0.3f, 0.14f);
    fillMidpointCircle(0.08f,  0.28f, 0.12f);
    fillMidpointCircle(-0.08f, 0.28f, 0.12f);
    fillMidpointCircle(0.05f,  0.38f, 0.11f);
    fillMidpointCircle(-0.05f, 0.38f, 0.11f);
    
    // 🥭 Ripe Mangoes (Yellow-Orange)
    glColor3f(1.0f, 0.7f, 0.1f); 
    float mangoPositions[][2] = { {0.04f,0.25f}, {-0.05f,0.28f}, {0.1f,0.32f}, {-0.08f,0.35f}, {0.02f,0.38f}, {-0.02f,0.4f}, {0.06f,0.33f}, {-0.04f,0.22f} };
    for(int i=0; i<8; i++) {
        float mx = mangoPositions[i][0]; float my = mangoPositions[i][1];
        glColor3f(0.2f, 0.1f, 0.0f); drawBresenhamLine(mx, my, mx, my + 0.02f); // Stem
        glColor3f(1.0f, 0.65f, 0.0f); fillMidpointCircle(mx, my, 0.018f); // Fruit
        glColor3f(1.0f, 0.4f, 0.0f); fillMidpointCircle(mx + 0.005f, my - 0.005f, 0.008f); // Blushed side
    }
    glPopMatrix();
}

void VillageScene::drawCoconutTree(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); glColor3f(0.7f, 0.5f, 0.3f);
    glBegin(GL_QUAD_STRIP); glVertex2f(-0.03f, 0.0f); glVertex2f(0.02f, 0.0f); glVertex2f(-0.01f, 0.45f); glVertex2f(0.01f, 0.45f);
    glEnd(); glTranslatef(0.0f, 0.45f, 0.0f); glColor3f(0.1f, 0.6f, 0.1f);
    for (int i = 0; i < 6; i++) { glRotatef(60, 0, 0, 1); glBegin(GL_TRIANGLES); glVertex2f(0, 0); glVertex2f(0.2f, 0.05f); glVertex2f(0.16f, -0.05f); glEnd(); }
    glPopMatrix();
}

void VillageScene::drawJackfruitTree(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); glColor3f(0.3f, 0.15f, 0.1f);
    glBegin(GL_QUADS); glVertex2f(-0.04f, 0.0f); glVertex2f(0.04f, 0.0f); glVertex2f(0.03f, 0.3f); glVertex2f(-0.03f, 0.3f);
    glEnd(); glColor3f(0.05f, 0.35f, 0.1f); fillMidpointCircle(0.0f, 0.4f, 0.2f);
    glPopMatrix();
}

void VillageScene::drawSun() {
    float rad = sunAngle * 3.1416f / 180.0f; 
    float x = 0.8f * cos(rad); 
    float y = 0.5f + 0.4f * sin(rad); // Orbit higher in the sky (above y=0.2 horizon)
    glPushMatrix(); glTranslatef(x, y, 0.0f); 
    glColor3f(1.0f, 0.85f, 0.0f); fillMidpointCircle(0.0f, 0.0f, 0.1f); 
    glPopMatrix();
}

void VillageScene::drawMoon() {
    float rad = (sunAngle - 180.0f) * 3.1416f / 180.0f; 
    float x = 0.8f * cos(rad); 
    float y = 0.5f + 0.4f * sin(rad); 
    glPushMatrix(); glTranslatef(x, y, 0.0f); 
    
    // 🌑 Draw Crescent Moon (Main circle - Offset circle)
    glColor3f(0.95f, 0.95f, 0.92f); 
    fillMidpointCircle(0.0f, 0.0f, 0.08f);
    
    // Background color subtraction for crescent effect
    float gTime = Application::getInstance().getGlobalTime();
    float intensity = sin(gTime * 3.14159f / 180.0f);
    float skyR = 0.4f, skyG = 0.6f, skyB = 0.8f;
    if (intensity > 0) {
        skyR = 0.4f + (0.1f * (1.0f - intensity));
        skyG = 0.6f + (0.2f * intensity);
        skyB = 0.8f + (0.2f * intensity);
    } else {
        float nightFactor = -intensity;
        skyR = 0.05f * (1.0f - nightFactor);
        skyG = 0.05f * (1.0f - nightFactor);
        skyB = 0.15f + (0.05f * (1.0f - nightFactor));
    }
    
    glColor3f(skyR, skyG, skyB); 
    fillMidpointCircle(0.03f, 0.02f, 0.07f); 
    glPopMatrix();
}

void VillageScene::drawStars() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (auto& s : stars) {
        // Twinkling light effect
        float twinkle = 0.5f + 0.5f * sin(sunAngle * 0.1f + s.phase);
        float brightness = 0.8f + 0.2f * twinkle;
        
        glPointSize(s.size * brightness);
        glBegin(GL_POINTS);
        glColor4f(1.0f, 1.0f, 0.9f, brightness);
        glVertex2f(s.x, s.y);
        glEnd();
    }
    glDisable(GL_BLEND);
}

void VillageScene::drawChildPark(float cx, float cy) {
    float pw = 0.38f; // park half-width
    float ph = 0.13f; // park half-height

    // ===== Soft Green Grass Ground =====
    glColor3f(0.25f, 0.72f, 0.28f);
    glBegin(GL_QUADS);
    glVertex2f(cx - pw, cy + ph);
    glVertex2f(cx + pw, cy + ph);
    glVertex2f(cx + pw, cy - ph);
    glVertex2f(cx - pw, cy - ph);
    glEnd();

    // Rubber play mat (center area - soft orange)
    glColor3f(0.88f, 0.65f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(cx - pw + 0.05f, cy + ph - 0.02f);
    glVertex2f(cx + pw - 0.05f, cy + ph - 0.02f);
    glVertex2f(cx + pw - 0.05f, cy - ph + 0.02f);
    glVertex2f(cx - pw + 0.05f, cy - ph + 0.02f);
    glEnd();

    // ===== Colorful Wooden Fence (all 4 sides) =====
    float fenceColors[][3] = {{0.9f,0.3f,0.3f},{0.3f,0.7f,0.3f},{0.3f,0.4f,0.9f},{0.9f,0.8f,0.2f},{0.8f,0.4f,0.8f}};
    int ci = 0;
    // Bottom fence
    for(float x = cx - pw; x <= cx + pw; x += 0.04f) {
        if(x > cx - 0.03f && x < cx + 0.03f) continue; // gate gap
        glColor3f(fenceColors[ci%5][0], fenceColors[ci%5][1], fenceColors[ci%5][2]);
        glBegin(GL_QUADS);
        glVertex2f(x, cy - ph);
        glVertex2f(x + 0.025f, cy - ph);
        glVertex2f(x + 0.025f, cy - ph + 0.04f);
        glVertex2f(x, cy - ph + 0.04f);
        glEnd();
        // Pointed top
        glBegin(GL_TRIANGLES);
        glVertex2f(x, cy - ph + 0.04f);
        glVertex2f(x + 0.025f, cy - ph + 0.04f);
        glVertex2f(x + 0.0125f, cy - ph + 0.05f);
        glEnd();
        ci++;
    }
    // Top fence
    for(float x = cx - pw; x <= cx + pw; x += 0.04f) {
        glColor3f(fenceColors[ci%5][0], fenceColors[ci%5][1], fenceColors[ci%5][2]);
        glBegin(GL_QUADS);
        glVertex2f(x, cy + ph);
        glVertex2f(x + 0.025f, cy + ph);
        glVertex2f(x + 0.025f, cy + ph + 0.04f);
        glVertex2f(x, cy + ph + 0.04f);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(x, cy + ph + 0.04f);
        glVertex2f(x + 0.025f, cy + ph + 0.04f);
        glVertex2f(x + 0.0125f, cy + ph + 0.05f);
        glEnd();
        ci++;
    }

    // Fence horizontal rails
    glColor3f(0.55f, 0.35f, 0.15f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx - pw, cy - ph + 0.02f); glVertex2f(cx + pw, cy - ph + 0.02f);
    glVertex2f(cx - pw, cy + ph + 0.02f); glVertex2f(cx + pw, cy + ph + 0.02f);
    glEnd();
    glLineWidth(1.0f);

    // ===== Entrance Arch =====
    glColor3f(0.85f, 0.2f, 0.2f);
    // Left post
    glBegin(GL_QUADS);
    glVertex2f(cx - 0.035f, cy - ph);
    glVertex2f(cx - 0.025f, cy - ph);
    glVertex2f(cx - 0.025f, cy - ph + 0.07f);
    glVertex2f(cx - 0.035f, cy - ph + 0.07f);
    glEnd();
    // Right post
    glBegin(GL_QUADS);
    glVertex2f(cx + 0.025f, cy - ph);
    glVertex2f(cx + 0.035f, cy - ph);
    glVertex2f(cx + 0.035f, cy - ph + 0.07f);
    glVertex2f(cx + 0.025f, cy - ph + 0.07f);
    glEnd();
    // Arch top
    glColor3f(0.95f, 0.85f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(cx - 0.04f, cy - ph + 0.06f);
    glVertex2f(cx + 0.04f, cy - ph + 0.06f);
    glVertex2f(cx + 0.04f, cy - ph + 0.075f);
    glVertex2f(cx - 0.04f, cy - ph + 0.075f);
    glEnd();

    // ===== Flower Beds (along top and bottom edges) =====
    float flowerColors[][3] = {{1.0f,0.3f,0.4f},{1.0f,0.85f,0.2f},{0.9f,0.4f,0.9f},{1.0f,0.5f,0.2f},{0.4f,0.8f,1.0f}};
    for(float fx = cx - pw + 0.03f; fx < cx + pw; fx += 0.06f) {
        int fc = (int)((fx + 5.0f) * 10) % 5;
        // Top edge flowers
        glColor3f(flowerColors[fc][0], flowerColors[fc][1], flowerColors[fc][2]);
        fillMidpointCircle(fx, cy + ph - 0.015f, 0.008f);
        // Flower center
        glColor3f(1.0f, 1.0f, 0.6f);
        fillMidpointCircle(fx, cy + ph - 0.015f, 0.003f);
        // Stem
        glColor3f(0.15f, 0.5f, 0.15f);
        glBegin(GL_LINES);
        glVertex2f(fx, cy + ph - 0.023f);
        glVertex2f(fx, cy + ph - 0.005f);
        glEnd();
    }

    // ===== 1. TWO SWINGS (left side) =====
    for(int sw = 0; sw < 2; sw++) {
        float swX = cx - 0.22f + sw * 0.08f;
        float swY = cy + 0.02f;
        // A-frame
        glColor3f(0.8f, 0.15f, 0.15f); // Red frame
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2f(swX - 0.03f, swY - 0.04f); glVertex2f(swX - 0.01f, swY + 0.09f);
        glVertex2f(swX + 0.03f, swY - 0.04f); glVertex2f(swX + 0.01f, swY + 0.09f);
        glEnd();
        // Top bar
        glBegin(GL_LINES);
        glVertex2f(swX - 0.015f, swY + 0.09f); glVertex2f(swX + 0.015f, swY + 0.09f);
        glEnd();
        glLineWidth(1.0f);
        // Rope + seat (animated, different phase per swing)
        float phase = sunAngle * 0.15f + sw * 1.5f;
        float sAngle = sin(phase) * 0.025f;
        // Left rope
        glColor3f(0.6f, 0.5f, 0.2f);
        glBegin(GL_LINES);
        glVertex2f(swX - 0.008f, swY + 0.09f); glVertex2f(swX - 0.008f + sAngle, swY + 0.01f);
        glVertex2f(swX + 0.008f, swY + 0.09f); glVertex2f(swX + 0.008f + sAngle, swY + 0.01f);
        glEnd();
        // Seat (wooden)
        glColor3f(0.6f, 0.35f, 0.15f);
        glBegin(GL_QUADS);
        glVertex2f(swX - 0.015f + sAngle, swY + 0.01f);
        glVertex2f(swX + 0.015f + sAngle, swY + 0.01f);
        glVertex2f(swX + 0.015f + sAngle, swY + 0.005f);
        glVertex2f(swX - 0.015f + sAngle, swY + 0.005f);
        glEnd();
    }

    // ===== 2. SLIDE (right side) - colorful =====
    float slX = cx + 0.22f;
    float slY = cy + 0.02f;
    // Ladder (blue)
    glColor3f(0.2f, 0.4f, 0.9f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(slX, slY - 0.04f); glVertex2f(slX, slY + 0.08f);
    glVertex2f(slX + 0.025f, slY - 0.04f); glVertex2f(slX + 0.025f, slY + 0.08f);
    glEnd();
    // Rungs
    for(float r = slY - 0.02f; r < slY + 0.08f; r += 0.018f) {
        glBegin(GL_LINES);
        glVertex2f(slX, r); glVertex2f(slX + 0.025f, r);
        glEnd();
    }
    glLineWidth(1.0f);
    // Platform
    glColor3f(0.2f, 0.4f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(slX - 0.02f, slY + 0.075f);
    glVertex2f(slX + 0.025f, slY + 0.08f);
    glVertex2f(slX + 0.025f, slY + 0.085f);
    glVertex2f(slX - 0.02f, slY + 0.08f);
    glEnd();
    // Slide surface (wide, yellow-orange gradient)
    glLineWidth(5.0f);
    glColor3f(0.95f, 0.75f, 0.1f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(slX - 0.02f, slY + 0.075f);
    glVertex2f(slX - 0.04f, slY + 0.05f);
    glVertex2f(slX - 0.06f, slY + 0.01f);
    glVertex2f(slX - 0.07f, slY - 0.03f);
    glVertex2f(slX - 0.07f, slY - 0.04f);
    glEnd();
    // Side rails
    glColor3f(0.9f, 0.3f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(slX - 0.015f, slY + 0.085f);
    glVertex2f(slX - 0.035f, slY + 0.06f);
    glVertex2f(slX - 0.055f, slY + 0.02f);
    glVertex2f(slX - 0.065f, slY - 0.02f);
    glEnd();
    glLineWidth(1.0f);

    // ===== 3. SEESAW (center) =====
    float ssX = cx - 0.02f;
    float ssY = cy - 0.02f;
    // Fulcrum (colored triangle)
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(ssX - 0.02f, ssY - 0.025f);
    glVertex2f(ssX + 0.02f, ssY - 0.025f);
    glVertex2f(ssX, ssY + 0.01f);
    glEnd();
    // Board (animated tilt)
    float tilt = sin(sunAngle * 0.12f) * 10.0f;
    glPushMatrix();
    glTranslatef(ssX, ssY + 0.01f, 0.0f);
    glRotatef(tilt, 0, 0, 1);
    // Board gradient
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.6f, 0.15f);
    glVertex2f(-0.07f, -0.005f);
    glVertex2f( 0.07f, -0.005f);
    glColor3f(0.8f, 0.4f, 0.1f);
    glVertex2f( 0.07f,  0.005f);
    glVertex2f(-0.07f,  0.005f);
    glEnd();
    // Handles (blue knobs)
    glColor3f(0.2f, 0.4f, 0.9f);
    fillMidpointCircle(-0.065f, 0.015f, 0.006f);
    fillMidpointCircle( 0.065f, 0.015f, 0.006f);
    glPopMatrix();

    // ===== 4. MERRY-GO-ROUND (center-right) =====
    float mgX = cx + 0.08f;
    float mgY = cy + 0.0f;
    // Base circle
    glColor3f(0.6f, 0.6f, 0.65f);
    fillMidpointCircle(mgX, mgY, 0.045f);
    // Inner circle
    glColor3f(0.7f, 0.7f, 0.75f);
    fillMidpointCircle(mgX, mgY, 0.035f);
    // Center post
    glColor3f(0.4f, 0.4f, 0.45f);
    fillMidpointCircle(mgX, mgY, 0.008f);
    // Rotating arms + colored seats
    float rot = sunAngle * 1.5f;
    glPushMatrix();
    glTranslatef(mgX, mgY, 0.0f);
    glRotatef(rot, 0, 0, 1);
    float armColors[][3] = {{0.95f,0.2f,0.2f}, {0.2f,0.75f,0.2f}, {0.2f,0.3f,0.95f}, {0.95f,0.85f,0.15f}, {0.9f,0.4f,0.9f}, {1.0f,0.5f,0.15f}};
    for(int i = 0; i < 6; i++) {
        float angle = i * 60.0f * 3.14159f / 180.0f;
        float ax = cos(angle) * 0.035f;
        float ay = sin(angle) * 0.035f;
        glColor3f(0.5f, 0.5f, 0.55f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(0, 0); glVertex2f(ax, ay);
        glEnd();
        glLineWidth(1.0f);
        glColor3f(armColors[i][0], armColors[i][1], armColors[i][2]);
        fillMidpointCircle(ax, ay, 0.009f);
    }
    glPopMatrix();

    // ===== Small Decorative Trees in park corners =====
    float treePos[][2] = {{cx - pw + 0.04f, cy + ph - 0.03f}, {cx + pw - 0.04f, cy + ph - 0.03f}};
    for(int t = 0; t < 2; t++) {
        // Trunk
        glColor3f(0.4f, 0.25f, 0.1f);
        glBegin(GL_QUADS);
        glVertex2f(treePos[t][0] - 0.005f, treePos[t][1] - 0.01f);
        glVertex2f(treePos[t][0] + 0.005f, treePos[t][1] - 0.01f);
        glVertex2f(treePos[t][0] + 0.004f, treePos[t][1] + 0.02f);
        glVertex2f(treePos[t][0] - 0.004f, treePos[t][1] + 0.02f);
        glEnd();
        // Canopy
        glColor3f(0.15f, 0.55f, 0.15f);
        fillMidpointCircle(treePos[t][0], treePos[t][1] + 0.035f, 0.022f);
        glColor3f(0.1f, 0.45f, 0.1f);
        fillMidpointCircle(treePos[t][0] + 0.01f, treePos[t][1] + 0.03f, 0.015f);
    }

    // ===== Sandbox (small, lower right) =====
    glColor3f(0.92f, 0.85f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(cx + 0.15f, cy - ph + 0.02f);
    glVertex2f(cx + 0.28f, cy - ph + 0.02f);
    glVertex2f(cx + 0.28f, cy - ph + 0.06f);
    glVertex2f(cx + 0.15f, cy - ph + 0.06f);
    glEnd();
    // Sandbox border
    glColor3f(0.6f, 0.4f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx + 0.15f, cy - ph + 0.02f);
    glVertex2f(cx + 0.28f, cy - ph + 0.02f);
    glVertex2f(cx + 0.28f, cy - ph + 0.06f);
    glVertex2f(cx + 0.15f, cy - ph + 0.06f);
    glEnd();
    glLineWidth(1.0f);
}