#include "village_scene.h"
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
    for (float x = -6.5f; x < 6.5f; x += 0.8f) {
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

    // Boats on River (y = 0.2 to 0.4)
    boats[0] = new Boat(-4.0f, 0.3f);
    boats[1] = new Boat( 1.5f, 0.35f);

    rain = new RainEffect();
    storm = new StormEffect();
    
    // Removed all extra people as requested
    /*
    for(int i=0; i<2; i++) {
        villagers.push_back(new Human(-3.0f + i*6.0f, -0.45f));
    }
    
    children.push_back(new Child(1.0f, -0.5f)); 
    */    
    // Fish INSIDE RIVER (y = 0.22 to 0.38)
    for (int i=0; i<10; i++) {
        schoolOfFish.push_back(new Fish(-5.5f + i*1.2f, 0.3f, 0.9f, 0.6f, 0.2f));
    }

    clouds[0] = new Cloud(-4.5f, 0.7f, 1.2f);
    clouds[1] = new Cloud(-1.0f, 0.8f, 0.9f);
    clouds[2] = new Cloud( 3.0f, 0.6f, 1.1f);
}

VillageScene::~VillageScene() {
    for(auto t : trees) delete t;
    for(int i=0; i<2; i++) delete boats[i];
    delete rain; delete storm;
    for(auto v : villagers) delete v;
    for(auto s : shopkeepers) delete s;
    for(auto c : children) delete c;
    for(auto f : schoolOfFish) delete f;
    for(int i=0; i<3; i++) delete clouds[i];
}

void VillageScene::update() {
    sunAngle += 0.08f;
    if (sunAngle > 360.0f) sunAngle = 0.0f;
    isNight = (sunAngle > 180.0f);

    for(auto t : trees) t->update(isWindy);
    for(int i=0; i<2; i++) boats[i]->update();
    
    if (isRainy || isStormy) rain->update();
    if (isStormy) storm->update();
    
    for(auto v : villagers) v->update();
    for(auto c : children) c->update();
    for(auto f : schoolOfFish) f->update();
    
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
    for(auto f : schoolOfFish) f->render();

    // Environment and Houses only on the field (y < 0.2)
    for(auto t : trees) t->render();
    for(auto& h : smallHouses) drawSmallHouse(h.x, h.y);
    
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
        drawHouseBoundary(hX, hY - 0.05f, 0.6f);
        drawRealisticVillageHouses(hX, hY);
        if (treeTypes[i] == 0) drawMangoTree(hX + 0.22f, hY);
        else if (treeTypes[i] == 1) drawCoconutTree(hX + 0.22f, hY);
        else drawJackfruitTree(hX + 0.22f, hY);
    }
    
    drawVillagePath();

    float stallColors[][3] = {{0.9f, 0.1f, 0.1f}, {0.1f, 0.8f, 0.2f}, {0.1f, 0.2f, 0.9f}, {0.9f, 0.8f, 0.1f}, {0.7f, 0.1f, 0.7f}, {0.9f, 0.5f, 0.1f}, {0.1f, 0.8f, 0.8f}};
    for(int i = 0; i < (int)shopLocations.size(); i++) {
        Prop& p = shopLocations[i];
        shopkeepers[i]->render();
        drawMarketShop(p.x, p.y, stallColors[p.type][0], stallColors[p.type][1], stallColors[p.type][2]);
    }

    for(auto v : villagers) v->render();
    for(auto c : children) c->render();

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
    float intensity = -sin(sunAngle * 3.14159f / 180.0f);
    glColor3f(0.05f * intensity, 0.05f * intensity, 0.15f * intensity); 
    fillMidpointCircle(0.03f, 0.02f, 0.07f); 
    glPopMatrix();
}

void VillageScene::drawStars() {
    glPointSize(1.5f); glBegin(GL_POINTS); glColor3f(1, 1, 1);
    for (int i = 0; i < 60; i++) { 
        float sx = (rand() % 400 - 200) / 100.0f; // Wide sky
        float sy = (rand() % 40 + 50) / 100.0f;  // Keep stars in high sky (above y=0.5)
        glVertex2f(sx, sy); 
    }
    glEnd();
}