#include "footpath.h"
#include <GL/glut.h>

Footpath::Footpath(float y, float width) {
    posY = y;
    footWidth = width;
}

void Footpath::render() {
    // ===== Brick Paver Base =====
    glColor3f(0.72f, 0.55f, 0.40f); // Warm brick color
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, posY);
    glVertex2f( 1.0f, posY);
    glVertex2f( 1.0f, posY - footWidth);
    glVertex2f(-1.0f, posY - footWidth);
    glEnd();

    // ===== Brick Pattern (horizontal rows + vertical joints) =====
    glColor3f(0.60f, 0.45f, 0.32f); // Darker grout lines
    glLineWidth(1.0f);

    // Horizontal grout lines
    glBegin(GL_LINES);
    float rowH = footWidth / 3.0f;
    for(int r = 0; r <= 3; r++) {
        float ly = posY - r * rowH;
        glVertex2f(-1.0f, ly);
        glVertex2f( 1.0f, ly);
    }
    glEnd();

    // Vertical grout lines (offset every other row for brick pattern)
    glBegin(GL_LINES);
    for(int r = 0; r < 3; r++) {
        float topY = posY - r * rowH;
        float botY = topY - rowH;
        float offset = (r % 2 == 0) ? 0.0f : 0.06f; // stagger
        for(float x = -1.0f + offset; x <= 1.0f; x += 0.12f) {
            glVertex2f(x, topY);
            glVertex2f(x, botY);
        }
    }
    glEnd();

    // ===== Top Curb (raised stone edge, building side) =====
    glColor3f(0.55f, 0.55f, 0.55f); // Stone gray
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, posY + 0.015f);
    glVertex2f( 1.0f, posY + 0.015f);
    glVertex2f( 1.0f, posY);
    glVertex2f(-1.0f, posY);
    glEnd();

    // Top curb highlight
    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, posY + 0.015f);
    glVertex2f( 1.0f, posY + 0.015f);
    glEnd();

    // ===== Bottom Curb (road side) =====
    glColor3f(0.45f, 0.45f, 0.45f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, posY - footWidth);
    glVertex2f( 1.0f, posY - footWidth);
    glVertex2f( 1.0f, posY - footWidth - 0.02f);
    glVertex2f(-1.0f, posY - footWidth - 0.02f);
    glEnd();

    // Curb shadow
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, posY - footWidth - 0.02f);
    glVertex2f( 1.0f, posY - footWidth - 0.02f);
    glEnd();

    // ===== Green Grass Strip (top edge, next to buildings) =====
    glColor3f(0.3f, 0.6f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, posY + 0.04f);
    glVertex2f( 1.0f, posY + 0.04f);
    glVertex2f( 1.0f, posY + 0.015f);
    glVertex2f(-1.0f, posY + 0.015f);
    glEnd();

    // Grass detail lines
    glColor3f(0.25f, 0.5f, 0.2f);
    glBegin(GL_LINES);
    for(float x = -1.0f; x <= 1.0f; x += 0.05f) {
        glVertex2f(x, posY + 0.015f);
        glVertex2f(x + 0.01f, posY + 0.04f);
    }
    glEnd();
}
