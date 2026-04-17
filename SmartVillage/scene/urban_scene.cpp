#include "urban_scene.h"
#include <GL/glut.h>
#include <cmath>

void UrbanScene::init() {
    sunAngle = 45.0f;
    isNight = false;
    isRainy = isStormy = isWindy = false;

    // Infrastructure
    school = new School(-0.6f, -0.1f);
    hospital = new Hospital(0.1f, -0.15f);
    
    buildings[0] = new Building(0.45f, -0.4f, 4, 0.2f, 0); // Office
    buildings[1] = new Building(0.68f, -0.4f, 5, 0.15f, 1); // Apartment
    buildings[2] = new Building(0.85f, -0.4f, 6, 0.18f, 0); // Office

    mainRoad = new Road(0.0f, -0.6f, 0.4f);
    trafficLight = new TrafficLight(-0.25f, -0.4f);

    for(int i=0; i<4; i++) {
        streetLights[i] = new LightingSystem(-0.8f + i*0.5f, -0.55f);
        citizens.push_back(new Human(-0.7f + i*0.4f, -0.65f));
    }
    
    for(int i=0; i<3; i++) {
        students.push_back(new Child(-0.8f + i*0.1f, -0.2f));
    }

    clouds[0] = new Cloud(-0.4f, 0.8f, 1.0f);
    clouds[1] = new Cloud( 0.4f, 0.7f, 1.2f);

    rain = new RainEffect();
    storm = new StormEffect();
}

UrbanScene::~UrbanScene() {
    delete school; delete hospital;
    for(int i=0; i<3; i++) delete buildings[i];
    delete mainRoad; delete trafficLight;
    for(int i=0; i<4; i++) delete streetLights[i];
    for(auto c : citizens) delete c;
    for(auto s : students) delete s;
    for(int i=0; i<2; i++) delete clouds[i];
    delete rain; delete storm;
}

void UrbanScene::update() {
    sunAngle += 0.2f;
    if (sunAngle > 360.0f) sunAngle = 0.0f;
    isNight = (sunAngle > 180.0f);

    float hour = ((sunAngle / 15.0f) + 6.0f);

    school->update(hour);
    hospital->update(0.016f); // approx dt
    trafficLight->update(1.0f);

    for(auto c : citizens) c->update();
    for(auto s : students) s->update();
    for(int i=0; i<4; i++) streetLights[i]->update(isNight);
    for(int i=0; i<2; i++) clouds[i]->update(isWindy, isStormy);

    if (isRainy || isStormy) rain->update();
    if (isStormy) storm->update();
}

void UrbanScene::render() {
    // Urban sky (slightly grayer)
    float intensity = sin(sunAngle * 3.14159f / 180.0f);
    float bgR = 0.6f, bgG = 0.7f, bgB = 0.8f;
    // Sky handled by Application
    (void)bgR; (void)bgG; (void)bgB;

    // Concrete Ground
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.52f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f( 1.0f, 0.0f);
    glColor3f(0.4f, 0.4f, 0.42f);
    glVertex2f( 1.0f,-1.0f);
    glVertex2f(-1.0f,-1.0f);
    glEnd();

    for(int i=0; i<2; i++) clouds[i]->render();
    
    school->render(isNight);
    hospital->render(isNight);
    for(int i=0; i<3; i++) buildings[i]->render(isNight);
    
    mainRoad->render();
    trafficLight->render();

    for(int i=0; i<4; i++) streetLights[i]->render();
    for(auto c : citizens) c->render();
    for(auto s : students) s->render();

    if (isStormy) storm->render();
    if (isRainy || isStormy) rain->render();
    // HUD handled by Application
}
