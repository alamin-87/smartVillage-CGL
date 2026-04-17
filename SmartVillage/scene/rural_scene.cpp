#include "rural_scene.h"
#include <GL/glut.h>
#include <cmath>
#include "../algorithms/midpoint_circle.h"
#include "../algorithms/bresenham.h"

void RuralScene::init() {
    sunAngle = 45.0f;
    isNight = false;
    isRainy = isStormy = isWindy = false;

    // We keep existing entities for interactivity, but we will place them around the new background
    for(int i=0; i<3; i++) clouds[i] = new Cloud(-0.5f + i*0.8f, 0.7f, 1.0f);

    // Entities
    father = new Human(-0.4f, -0.6f);
    mother = new Human(-0.2f, -0.55f);
    child1 = new Child(0.0f, -0.7f);
    child2 = new Child(0.3f, -0.6f);

    cow = new Cow(0.6f, -0.4f);
    goat = new Goat(0.5f, -0.6f);
    duck = new Duck(0.8f, -0.75f);
    hen = new Hen(0.2f, -0.8f);

    rain = new RainEffect();
    storm = new StormEffect();
    
    // Unused pointers set to null
    for(int i=0; i<5; i++) trees[i] = nullptr;
    familyHouse = nullptr; shed = nullptr; pump = nullptr; pole = nullptr;
}

RuralScene::~RuralScene() {
    for(int i=0; i<3; i++) delete clouds[i];
    delete father; delete mother; delete child1; delete child2;
    delete cow; delete goat; delete duck; delete hen;
    delete rain; delete storm;
}

void RuralScene::update() {
    sunAngle += 0.2f;
    if (sunAngle > 360.0f) sunAngle = 0.0f;
    isNight = (sunAngle > 180.0f);
    
    for(int i=0; i<3; i++) clouds[i]->update(isWindy, isStormy);
    
    father->update(); mother->update();
    child1->update(); child2->update();
    cow->update(isNight); goat->update(); duck->update(); hen->update();

    if (isRainy || isStormy) rain->update();
    if (isStormy) storm->update();
}

void RuralScene::render() {
    drawFields();

    for(int i=0; i<3; i++) clouds[i]->render();
    
    // Draw the realistic background elements based on reference image
    drawPalmTree(-0.6f, -0.4f);
    drawBushyTree(0.4f, 0.05f);
    drawRealisticHouses(0.2f, -0.3f);
    drawWoodenFence(0.8f, -0.2f);
    
    drawPond();

    // Render animals and people over the new realistic path
    cow->render();
    goat->render();
    duck->render();
    hen->render();

    father->render();
    mother->render();
    child1->render();
    child2->render();

    if (isStormy) storm->render();
    if (isRainy || isStormy) rain->render();
}

void RuralScene::drawFields() {
    // 1. River in the background (y = 0.0 to 1.0 roughly, but we draw it mid-scene)
    glColor3f(0.15f, 0.5f, 0.9f); // Deep blue river
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.3f);
        glVertex2f( 1.0f, 0.3f);
        glVertex2f( 1.0f, -0.1f);
        glVertex2f(-1.0f, -0.1f);
    glEnd();
    
    // Far riverbank strip
    glColor3f(0.2f, 0.6f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.3f);
        glVertex2f( 1.0f, 0.3f);
        glVertex2f( 1.0f, 0.35f);
        glVertex2f(-1.0f, 0.35f);
    glEnd();

    // 2. Curved main grass ground
    glColor3f(0.3f, 0.7f, 0.1f); // Vibrant grass green
    glBegin(GL_QUADS);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f( 1.0f, -0.1f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
    
    // Left curve 
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(-0.7f, -1.0f);
    glEnd();

    // 3. Winding Dirt Path (Yellow/Sand color)
    glColor3f(0.85f, 0.7f, 0.4f);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.1f, -0.3f); glVertex2f(0.5f, -0.3f); // Top near house
        glVertex2f(0.15f, -0.5f); glVertex2f(0.6f, -0.5f);
        glVertex2f(-0.1f, -0.7f); glVertex2f(0.4f, -0.7f);
        glVertex2f(-0.4f, -0.9f); glVertex2f(0.3f, -0.9f);
        glVertex2f(-0.5f, -1.0f); glVertex2f(0.2f, -1.0f); // Bottom 
    glEnd();
}

void RuralScene::drawRealisticHouses(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Two connected houses
    for (int h = 0; h < 2; h++) {
        float hx = (h == 0) ? -0.2f : 0.15f;
        float hy = (h == 0) ? -0.05f : 0.0f; // Left house slightly lower
        float w = (h == 0) ? 0.35f : 0.3f;
        
        // Base Wall (White)
        glColor3f(0.95f, 0.95f, 0.95f);
        glBegin(GL_QUADS);
            glVertex2f(hx - w/2, hy);
            glVertex2f(hx + w/2, hy);
            glVertex2f(hx + w/2, hy + 0.15f);
            glVertex2f(hx - w/2, hy + 0.15f);
        glEnd();
        
        // Shading edge to make it look 3D
        glColor3f(0.85f, 0.85f, 0.85f);
        glBegin(GL_QUADS);
            glVertex2f(hx - w/2, hy);
            glVertex2f(hx - w/2 + 0.05f, hy);
            glVertex2f(hx - w/2 + 0.05f, hy + 0.15f);
            glVertex2f(hx - w/2, hy + 0.15f);
        glEnd();
        
        // Roof (Bright Orange with yellow highlight)
        glColor3f(1.0f, 0.3f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(hx - w/2 - 0.05f, hy + 0.15f);
            glVertex2f(hx + w/2 + 0.05f, hy + 0.15f);
            glVertex2f(hx, hy + 0.28f);
        glEnd();
        // Roof Trim/Highlight
        glColor3f(1.0f, 0.6f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(hx - w/2 - 0.05f, hy + 0.15f);
            glVertex2f(hx - w/2 + 0.05f, hy + 0.15f);
            glVertex2f(hx, hy + 0.28f);
        glEnd();
        
        // Door (Dark)
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(hx + 0.05f, hy);
            glVertex2f(hx + 0.15f, hy);
            glVertex2f(hx + 0.15f, hy + 0.1f);
            glVertex2f(hx + 0.05f, hy + 0.1f);
        glEnd();
        
        // Window (Black with Bars)
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(hx - 0.15f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.1f);
            glVertex2f(hx - 0.15f, hy + 0.1f);
        glEnd();
        // Window Bars
        glColor3f(0.8f, 0.8f, 0.8f);
        drawBresenhamLine(hx - 0.12f, hy + 0.05f, hx - 0.12f, hy + 0.1f);
        drawBresenhamLine(hx - 0.10f, hy + 0.05f, hx - 0.10f, hy + 0.1f);
        drawBresenhamLine(hx - 0.08f, hy + 0.05f, hx - 0.08f, hy + 0.1f);
    }
    
    glPopMatrix();
}

void RuralScene::drawBushyTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Thick branched trunk
    glColor3f(0.5f, 0.3f, 0.1f); // Dark Tree Brown
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, 0.0f);
        glVertex2f( 0.04f, 0.0f);
        glVertex2f( 0.06f, 0.2f);
        glVertex2f( 0.1f,  0.3f);
        glVertex2f( 0.0f,  0.3f);
        glVertex2f(-0.05f, 0.2f);
    glEnd();
    
    // Big Bushy Leaves clusters (Using Triangles for standard shapes)
    // Darker back leaves
    glColor3f(0.1f, 0.5f, 0.1f); 
    fillMidpointCircle(0.0f, 0.3f, 0.15f);
    fillMidpointCircle(0.1f, 0.25f, 0.18f);
    fillMidpointCircle(-0.1f, 0.35f, 0.14f);
    
    // Lighter front leaves
    glColor3f(0.2f, 0.7f, 0.15f); 
    fillMidpointCircle(0.05f, 0.32f, 0.12f);
    fillMidpointCircle(-0.05f, 0.28f, 0.15f);
    
    glPopMatrix();
}

void RuralScene::drawPalmTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Tall curved trunk
    glColor3f(0.7f, 0.45f, 0.2f);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(-0.05f, 0.0f);   glVertex2f(0.02f, 0.0f);
        glVertex2f(-0.03f, 0.15f);  glVertex2f(0.015f, 0.15f);
        glVertex2f(-0.01f, 0.3f);   glVertex2f(0.01f, 0.3f);
        glVertex2f(0.0f, 0.45f);    glVertex2f(0.01f, 0.45f);
    glEnd();
    
    // Texture rings on trunk
    glColor3f(0.5f, 0.3f, 0.1f);
    for (float ty = 0.05f; ty < 0.45f; ty += 0.05f) {
        float tx = -0.05f * (1.0f - ty/0.45f);
        drawBresenhamLine(tx, ty, tx + 0.04f, ty + 0.01f);
    }
    
    // Palm Fronds
    glColor3f(0.15f, 0.6f, 0.2f);
    glTranslatef(0.005f, 0.45f, 0.0f); // Move to top of trunk
    for (int i = 0; i < 8; i++) {
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(-0.02f, 0.15f);
            glVertex2f(0.02f, 0.18f);
        glEnd();
        
        // Frond leaves detail
        glColor3f(0.1f, 0.5f, 0.15f);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.01f, 0.15f);
            glVertex2f(0.04f, 0.15f);
        glEnd();
        glColor3f(0.15f, 0.6f, 0.2f); // reset color
    }
    
    glPopMatrix();
}

void RuralScene::drawWoodenFence(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.4f, 0.25f, 0.1f); // Wood color
    
    // Horizontal beams
    drawBresenhamLine(0.0f, 0.02f, 0.25f, 0.02f);
    drawBresenhamLine(0.0f, 0.06f, 0.25f, 0.06f);
    
    // Vertical posts
    for (float px = 0.02f; px < 0.25f; px += 0.05f) {
        glBegin(GL_QUADS);
            glVertex2f(px - 0.005f, 0.0f);
            glVertex2f(px + 0.005f, 0.0f);
            glVertex2f(px + 0.005f, 0.1f);
            glVertex2f(px - 0.005f, 0.1f);
        glEnd();
    }
    glPopMatrix();
}

void RuralScene::drawPond() {
    glPushMatrix();
    glTranslatef(0.8f, -0.75f, 0.0f); // Near duck
    glScalef(2.0f, 0.5f, 1.0f);
    if (!isNight) glColor3f(0.2f, 0.5f, 0.8f);
    else glColor3f(0.1f, 0.2f, 0.4f);
    fillMidpointCircle(0.0f, 0.0f, 0.1f); // Solid pond using new func
    glPopMatrix();
}
