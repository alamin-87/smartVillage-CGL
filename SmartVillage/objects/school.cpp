#include "school.h"
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include "../algorithms/bresenham.h"
#include "../algorithms/midpoint_circle.h"

School::School(float x, float y) {
    posX = x; posY = y;
    flagWave = 0.0f; bellRinging = false;
    ballX = 0.0f; ballY = -0.125f; ballAngle = 0.0f;
}

void School::update(float hour) {
    flagWave += 0.1f;
    bellRinging = (((int)hour == 8) || ((int)hour == 12) || ((int)hour == 15));
    
    // Football animation (rolling/bouncing)
    ballAngle += 5.0f;
    ballX = sin(flagWave * 0.5f) * 0.15f; // Roll left and right
    ballY = -0.125f + fabsf(sin(flagWave * 2.0f)) * 0.02f; // Slight bounce
}

void School::render(bool isNight) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Main building - 2 storey
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f( 0.3f, 0.0f);
        glVertex2f( 0.3f, 0.3f);
        glVertex2f(-0.3f, 0.3f);
    glEnd();

    // Floor division line
    glColor3f(0.6f, 0.55f, 0.5f);
    drawBresenhamLine(-0.3f, 0.15f, 0.3f, 0.15f);

    // Windows grid (3 cols x 2 rows)
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            float wx = -0.2f + col * 0.15f;
            float wy = 0.04f + row * 0.15f;
            if (isNight) glColor3f(0.9f, 0.8f, 0.3f);
            else glColor3f(0.5f, 0.7f, 0.9f);
            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.08f, wy);
                glVertex2f(wx + 0.08f, wy + 0.08f);
                glVertex2f(wx, wy + 0.08f);
            glEnd();
            // Window frame
            glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_LINE_LOOP);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.08f, wy);
                glVertex2f(wx + 0.08f, wy + 0.08f);
                glVertex2f(wx, wy + 0.08f);
            glEnd();
            // Cross
            drawBresenhamLine(wx + 0.04f, wy, wx + 0.04f, wy + 0.08f);
            drawBresenhamLine(wx, wy + 0.04f, wx + 0.08f, wy + 0.04f);
        }
    }

    // Entrance door
    glColor3f(0.4f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f( 0.04f, 0.0f);
        glVertex2f( 0.04f, 0.12f);
        glVertex2f(-0.04f, 0.12f);
    glEnd();

    // Steps
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(-0.06f, 0.0f);
        glVertex2f( 0.06f, 0.0f);
        glVertex2f( 0.06f, -0.02f);
        glVertex2f(-0.06f, -0.02f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.08f, -0.02f);
        glVertex2f( 0.08f, -0.02f);
        glVertex2f( 0.08f, -0.04f);
        glVertex2f(-0.08f, -0.04f);
    glEnd();

    // Roof
    glColor3f(0.6f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.32f, 0.3f);
        glVertex2f( 0.32f, 0.3f);
        glVertex2f( 0.32f, 0.33f);
        glVertex2f(-0.32f, 0.33f);
    glEnd();

    // Sign board
    glColor3f(0.15f, 0.35f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.33f);
        glVertex2f( 0.25f, 0.33f);
        glVertex2f( 0.25f, 0.38f);
        glVertex2f(-0.25f, 0.38f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    const char* name = "GOVT PRIMARY SCHOOL";
    glRasterPos2f(-0.2f, 0.345f);
    for (int i = 0; i < (int)strlen(name); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);

    // Flag pole
    drawFlag();

    // Boundary fence
    glColor3f(0.3f, 0.3f, 0.3f);
    drawBresenhamLine(-0.35f, 0.0f, -0.35f, 0.1f);
    drawBresenhamLine( 0.35f, 0.0f,  0.35f, 0.1f);
    drawBresenhamLine(-0.35f, 0.1f,  0.35f, 0.1f);
    drawBresenhamLine(-0.35f, 0.05f, 0.35f, 0.05f);

    // Football field
    drawField();

    // Bell indicator
    if (bellRinging) {
        glColor3f(1.0f, 0.8f, 0.0f);
        fillMidpointCircle(0.0f, 0.4f, 0.015f);
    }

    glPopMatrix();
}

void School::drawFlag() {
    // Pole
    glColor3f(0.5f, 0.5f, 0.5f);
    drawBresenhamLine(-0.28f, 0.0f, -0.28f, 0.45f);

    // Flag (waving using sine)
    float wave = sin(flagWave) * 0.01f;
    
    // Green base (Bangladesh flag)
    glColor3f(0.0f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.28f, 0.35f);
        glVertex2f(-0.16f + wave, 0.35f);
        glVertex2f(-0.16f + wave, 0.45f);
        glVertex2f(-0.28f, 0.45f);
    glEnd();
    
    // Red circle
    glColor3f(0.85f, 0.15f, 0.15f);
    fillMidpointCircle(-0.23f + wave * 0.5f, 0.4f, 0.025f);
}

void School::drawField() {
    // Football field below school
    glColor3f(0.15f, 0.55f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, -0.05f);
        glVertex2f( 0.25f, -0.05f);
        glVertex2f( 0.25f, -0.2f);
        glVertex2f(-0.25f, -0.2f);
    glEnd();

    // Field markings (white lines)
    glColor3f(1.0f, 1.0f, 1.0f);
    // Boundary
    drawBresenhamLine(-0.24f, -0.06f, 0.24f, -0.06f);
    drawBresenhamLine(-0.24f, -0.19f, 0.24f, -0.19f);
    drawBresenhamLine(-0.24f, -0.06f, -0.24f, -0.19f);
    drawBresenhamLine( 0.24f, -0.06f,  0.24f, -0.19f);
    // Centre line
    drawBresenhamLine(0.0f, -0.06f, 0.0f, -0.19f);
    // Centre circle
    fillMidpointCircle(0.0f, -0.125f, 0.04f);
    // Goal posts
    drawBresenhamLine(-0.24f, -0.10f, -0.24f, -0.15f);
    drawBresenhamLine(-0.24f, -0.10f, -0.22f, -0.10f);
    drawBresenhamLine(-0.24f, -0.15f, -0.22f, -0.15f);
    drawBresenhamLine( 0.24f, -0.10f,  0.24f, -0.15f);
    drawBresenhamLine( 0.24f, -0.15f,  0.22f, -0.15f);

    // Improved Football Drawing
    glPushMatrix();
    glTranslatef(ballX, ballY, 0.0f);
    glRotatef(ballAngle, 0.0f, 0.0f, 1.0f);

    // Ball Body
    glColor3f(1.0f, 1.0f, 1.0f);
    fillMidpointCircle(0.0f, 0.0f, 0.015f);
    
    // Better Football Pattern (Hexagon-like spots)
    glColor3f(0.1f, 0.1f, 0.1f);
    // Center spot
    fillMidpointCircle(0.0f, 0.0f, 0.006f);
    // Surround spots
    for(int i=0; i<5; i++) {
        float ang = i * (360.0f/5.0f) * 3.14159f / 180.0f;
        fillMidpointCircle(cos(ang) * 0.01f, sin(ang) * 0.01f, 0.004f);
    }
    glPopMatrix();
}
