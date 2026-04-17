#include "rural_scene.h"
#include "../app/application.h"
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

    // Entities with specific roles
    // Father standing near the fence and pond
    father = new Human(0.8f, -0.4f);
    father->setSpeed(0.0f);

    // Mother sitting outside the house
    mother = new Human(0.1f, -0.32f);
    mother->setSitting(true);
    mother->setSpeed(0.0f);

    // Children playing in the rural park
    // Child 1 on left swing
    child1 = new Child(-0.52f, -0.47f);
    child1->setSpeed(0.0f); child1->setPlaying(true); child1->setChildScale(0.45f);

    // Child 2 on right swing
    child2 = new Child(-0.435f, -0.47f);
    child2->setSpeed(0.0f); child2->setPlaying(true); child2->setChildScale(0.45f);

    // Child 3 on slide
    child3 = new Child(-0.84f, -0.36f);
    child3->setSpeed(0.0f); child3->setPlaying(true); child3->setChildScale(0.45f);

    // Child 4 walking playfully
    child4 = new Child(-0.6f, -0.6f);
    child4->setSpeed(0.003f); child4->setBounds(-0.9f, -0.2f);
    
    // Child 5 watching duck
    child5 = new Child(0.65f, -0.75f);
    child5->setSpeed(0.0f);

    // Distant children running/playing in the background farmlands (4-5 kids)
    Child* dc1 = new Child(-0.35f, 0.08f); dc1->setChildScale(0.25f); dc1->setSpeed(0.001f); dc1->setBounds(-0.45f, -0.2f); dc1->setPlaying(true);
    Child* dc2 = new Child(-0.25f, 0.08f); dc2->setChildScale(0.25f); dc2->setSpeed(0.0f); dc2->setPlaying(true);
    Child* dc3 = new Child(0.25f, 0.05f);  dc3->setChildScale(0.3f);  dc3->setSpeed(0.002f);  dc3->setBounds(-0.2f, 0.45f); dc3->setPlaying(true);
    Child* dc4 = new Child(-0.75f, 0.12f); dc4->setChildScale(0.2f);  dc4->setSpeed(0.0015f); dc4->setBounds(-0.9f, -0.6f); dc4->setPlaying(true);
    Child* dc5 = new Child(-0.05f, 0.15f); dc5->setChildScale(0.2f);  dc5->setSpeed(0.0f);    dc5->setPlaying(true);

    distantChildren.push_back(dc1);
    distantChildren.push_back(dc2);
    distantChildren.push_back(dc3);
    distantChildren.push_back(dc4);
    distantChildren.push_back(dc5);

    cow = new Cow(0.5f, -0.4f);
    goat = new Goat(0.6f, -0.55f);
    duck = new Duck(0.75f, -0.75f);
    hen = new Hen(0.15f, -0.35f);

    rain = new RainEffect();
    storm = new StormEffect();
    
    // Unused pointers set to null
    for(int i=0; i<5; i++) trees[i] = nullptr;
    familyHouse = nullptr; shed = nullptr; pump = nullptr; pole = nullptr;
}

RuralScene::~RuralScene() {
    for(int i=0; i<3; i++) delete clouds[i];
    delete father; delete mother; delete child1; delete child2;
    delete child3; delete child4; delete child5;
    for(auto dc : distantChildren) delete dc;
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
    child3->update(); child4->update(); child5->update();
    for(auto dc : distantChildren) dc->update();
    cow->update(isNight); goat->update(); duck->update(); hen->update();

    if (isRainy || isStormy) rain->update();
    if (isStormy) storm->update();
}

void RuralScene::render() {
    drawFields();

    for(int i=0; i<3; i++) clouds[i]->render();
    
    // Distant background children
    for(auto dc : distantChildren) dc->render();
    
    // Trees — repositioned away from river
    drawPalmTree(-0.6f, -0.4f);
    drawBushyTree(-0.3f, -0.15f);
    
    // Mango trees in the field (like Scene 1)
    drawMangoTree(0.65f, -0.1f);
    drawMangoTree(-0.85f, -0.05f);
    drawMangoTree(0.15f, 0.05f);
    
    // Houses — original pair + additional small houses
    drawRealisticHouses(0.2f, -0.3f);
    drawSmallHouse(-0.4f, -0.25f);
    drawSmallHouse(0.75f, -0.35f);
    
    drawWoodenFence(0.85f, -0.2f);
    drawPond();

    // Draw the children's park on the left side
    drawChildPark(-0.75f, -0.5f);

    // Render animals and people
    cow->render();
    goat->render();
    duck->render();
    hen->render();

    father->render();
    mother->render();
    child1->render();
    child2->render();
    
    // Render the park children
    child3->render();
    child4->render();
    child5->render();

    // Render Alamin (Main Character)
    Application::getInstance().getAlamin()->render();

    if (isStormy) storm->render();
    if (isRainy || isStormy) rain->render();
}

void RuralScene::drawFields() {
    // 1. Beautiful lush green ground
    glColor3f(0.25f, 0.65f, 0.15f); 
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.35f);
        glVertex2f( 1.0f, 0.35f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    // 2. Farmland (Crop Rows) in the background
    glColor3f(0.45f, 0.3f, 0.15f); // Brown soil
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, 0.2f);
        glVertex2f( 0.4f, 0.2f);
        glVertex2f( 0.5f, -0.05f);
        glVertex2f(-1.0f, -0.05f);
    glEnd();
    
    // Green crop lines
    glColor3f(0.6f, 0.8f, 0.2f);
    glLineWidth(3.0f);
    for(float row = -0.85f; row < 0.45f; row += 0.1f) {
        float shift = (row + 1.0f) * 0.1f;
        glBegin(GL_LINES);
            glVertex2f(row, 0.2f);
            glVertex2f(row - shift, -0.05f);
        glEnd();
    }
    glLineWidth(1.0f);

    // 3. Winding Dirt Path (Rich sand color)
    glColor3f(0.82f, 0.72f, 0.50f);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.1f, -0.3f); glVertex2f(0.5f, -0.3f); 
        glVertex2f(0.15f, -0.5f); glVertex2f(0.65f, -0.45f);
        glVertex2f(-0.1f, -0.7f); glVertex2f(0.5f, -0.65f);
        glVertex2f(-0.4f, -0.9f); glVertex2f(0.3f, -0.9f);
        glVertex2f(-0.5f, -1.0f); glVertex2f(0.2f, -1.0f);  
    glEnd();
}

void RuralScene::drawRealisticHouses(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Two connected houses
    for (int h = 0; h < 2; h++) {
        float hx = (h == 0) ? -0.2f : 0.15f;
        float hy = (h == 0) ? -0.05f : 0.0f;
        float w = (h == 0) ? 0.35f : 0.3f;
        
        // Base Wall (Cream White)
        glColor3f(0.95f, 0.93f, 0.88f);
        glBegin(GL_QUADS);
            glVertex2f(hx - w/2, hy);
            glVertex2f(hx + w/2, hy);
            glVertex2f(hx + w/2, hy + 0.15f);
            glVertex2f(hx - w/2, hy + 0.15f);
        glEnd();
        
        // Shading edge to make it look 3D
        glColor3f(0.85f, 0.83f, 0.78f);
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
        
        // Door (Brown wood with frame)
        glColor3f(0.4f, 0.22f, 0.08f);
        glBegin(GL_QUADS);
            glVertex2f(hx + 0.03f, hy);
            glVertex2f(hx + 0.11f, hy);
            glVertex2f(hx + 0.11f, hy + 0.1f);
            glVertex2f(hx + 0.03f, hy + 0.1f);
        glEnd();
        // Door frame
        glColor3f(0.3f, 0.15f, 0.05f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(hx + 0.03f, hy);
            glVertex2f(hx + 0.11f, hy);
            glVertex2f(hx + 0.11f, hy + 0.1f);
            glVertex2f(hx + 0.03f, hy + 0.1f);
        glEnd();
        // Door knob
        glColor3f(0.8f, 0.7f, 0.2f);
        fillMidpointCircle(hx + 0.095f, hy + 0.05f, 0.005f);
        // Door center line
        glColor3f(0.3f, 0.15f, 0.05f);
        drawBresenhamLine(hx + 0.07f, hy + 0.005f, hx + 0.07f, hy + 0.095f);

        // Left Window (Blue glass with frame)
        glColor3f(0.5f, 0.75f, 0.95f);
        glBegin(GL_QUADS);
            glVertex2f(hx - 0.14f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.11f);
            glVertex2f(hx - 0.14f, hy + 0.11f);
        glEnd();
        // Window frame
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(hx - 0.14f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.05f);
            glVertex2f(hx - 0.05f, hy + 0.11f);
            glVertex2f(hx - 0.14f, hy + 0.11f);
        glEnd();
        // Window cross bars
        drawBresenhamLine(hx - 0.095f, hy + 0.05f, hx - 0.095f, hy + 0.11f);
        drawBresenhamLine(hx - 0.14f, hy + 0.08f, hx - 0.05f, hy + 0.08f);
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

void RuralScene::drawMangoTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Realistic Thick Trunk
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

    // Dense Bushy Canopy
    glColor3f(0.05f, 0.3f, 0.05f); 
    fillMidpointCircle(0.0f,   0.3f, 0.14f);
    fillMidpointCircle(0.08f,  0.28f, 0.12f);
    fillMidpointCircle(-0.08f, 0.28f, 0.12f);
    fillMidpointCircle(0.05f,  0.38f, 0.11f);
    fillMidpointCircle(-0.05f, 0.38f, 0.11f);
    
    // Ripe Mangoes (Yellow-Orange)
    float mangoPositions[][2] = { {0.04f,0.25f}, {-0.05f,0.28f}, {0.1f,0.32f}, {-0.08f,0.35f}, {0.02f,0.38f}, {-0.02f,0.4f} };
    for(int i=0; i<6; i++) {
        float mx = mangoPositions[i][0]; float my = mangoPositions[i][1];
        glColor3f(0.2f, 0.1f, 0.0f); drawBresenhamLine(mx, my, mx, my + 0.02f);
        glColor3f(1.0f, 0.65f, 0.0f); fillMidpointCircle(mx, my, 0.018f);
        glColor3f(1.0f, 0.4f, 0.0f); fillMidpointCircle(mx + 0.005f, my - 0.005f, 0.008f);
    }
    glPopMatrix();
}

void RuralScene::drawSmallHouse(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Wall
    glColor3f(0.95f, 0.9f, 0.82f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.0f); glVertex2f(0.1f, 0.0f);
        glVertex2f(0.1f, 0.1f); glVertex2f(-0.1f, 0.1f);
    glEnd();
    
    // Roof (Red-Orange)
    glColor3f(0.85f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.12f, 0.1f); glVertex2f(0.12f, 0.1f); glVertex2f(0.0f, 0.2f);
    glEnd();
    
    // Door (Brown)
    glColor3f(0.4f, 0.22f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.0f); glVertex2f(0.02f, 0.0f);
        glVertex2f(0.02f, 0.06f); glVertex2f(-0.02f, 0.06f);
    glEnd();
    // Door frame
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.02f, 0.0f); glVertex2f(0.02f, 0.0f);
        glVertex2f(0.02f, 0.06f); glVertex2f(-0.02f, 0.06f);
    glEnd();
    // Door knob
    glColor3f(0.8f, 0.7f, 0.2f);
    fillMidpointCircle(0.015f, 0.03f, 0.003f);
    
    // Left Window (Blue glass with frame)
    glColor3f(0.5f, 0.75f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, 0.04f); glVertex2f(-0.04f, 0.04f);
        glVertex2f(-0.04f, 0.08f); glVertex2f(-0.08f, 0.08f);
    glEnd();
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.08f, 0.04f); glVertex2f(-0.04f, 0.04f);
        glVertex2f(-0.04f, 0.08f); glVertex2f(-0.08f, 0.08f);
    glEnd();
    drawBresenhamLine(-0.06f, 0.04f, -0.06f, 0.08f);
    drawBresenhamLine(-0.08f, 0.06f, -0.04f, 0.06f);
    
    // Right Window (Blue glass with frame)
    glColor3f(0.5f, 0.75f, 0.95f);
    glBegin(GL_QUADS);
        glVertex2f(0.04f, 0.04f); glVertex2f(0.08f, 0.04f);
        glVertex2f(0.08f, 0.08f); glVertex2f(0.04f, 0.08f);
    glEnd();
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.04f, 0.04f); glVertex2f(0.08f, 0.04f);
        glVertex2f(0.08f, 0.08f); glVertex2f(0.04f, 0.08f);
    glEnd();
    drawBresenhamLine(0.06f, 0.04f, 0.06f, 0.08f);
    drawBresenhamLine(0.04f, 0.06f, 0.08f, 0.06f);
    
    glPopMatrix();
}

void RuralScene::drawChildPark(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Slide Structure
    glColor3f(0.2f, 0.5f, 0.8f); // Blue frame
    drawBresenhamLine(-0.1f, 0.0f, -0.1f, 0.15f); // Left post
    drawBresenhamLine(-0.05f, 0.0f, -0.05f, 0.15f); // Right post
    drawBresenhamLine(-0.1f, 0.15f, -0.05f, 0.15f); // Top bar
    
    // Steps
    glColor3f(0.6f, 0.6f, 0.6f);
    drawBresenhamLine(-0.1f, 0.05f, -0.05f, 0.05f);
    drawBresenhamLine(-0.1f, 0.1f, -0.05f, 0.1f);
    
    // The Slide itself (Red)
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.15f);
        glVertex2f(-0.05f, 0.13f);
        glVertex2f(0.08f, 0.0f);
        glVertex2f(0.1f, 0.0f);
    glEnd();

    // Swing Structure
    glColor3f(0.8f, 0.5f, 0.2f); // Orange-ish frame
    drawBresenhamLine(0.15f, 0.0f, 0.2f, 0.15f); // Left leg angled
    drawBresenhamLine(0.25f, 0.0f, 0.2f, 0.15f); // Right leg angled
    drawBresenhamLine(0.2f, 0.15f, 0.35f, 0.15f); // Top crossbar
    drawBresenhamLine(0.35f, 0.15f, 0.3f, 0.0f); // Far leg left
    drawBresenhamLine(0.35f, 0.15f, 0.4f, 0.0f); // Far leg right

    // The Swings
    glColor3f(0.4f, 0.4f, 0.4f); // Ropes
    drawBresenhamLine(0.23f, 0.15f, 0.23f, 0.05f);
    drawBresenhamLine(0.27f, 0.15f, 0.27f, 0.05f);

    drawBresenhamLine(0.3f, 0.15f, 0.3f, 0.05f);
    drawBresenhamLine(0.33f, 0.15f, 0.33f, 0.05f);
    
    glColor3f(0.1f, 0.6f, 0.2f); // Swing Seats (green)
    glBegin(GL_QUADS);
        glVertex2f(0.23f, 0.04f); glVertex2f(0.27f, 0.04f);
        glVertex2f(0.27f, 0.05f); glVertex2f(0.23f, 0.05f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.3f, 0.04f); glVertex2f(0.33f, 0.04f);
        glVertex2f(0.33f, 0.05f); glVertex2f(0.3f, 0.05f);
    glEnd();
    
    glPopMatrix();
}
