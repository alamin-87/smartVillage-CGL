#include "renderer.h"
#include <GL/glut.h>
#include <cstring>

namespace Renderer {

    void drawRect(float x, float y, float w, float h, float r, float g, float b) {
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y + h);
            glVertex2f(x, y + h);
        glEnd();
    }

    void drawRectAlpha(float x, float y, float w, float h, float r, float g, float b, float a) {
        enableBlend();
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y + h);
            glVertex2f(x, y + h);
        glEnd();
        disableBlend();
    }

    void drawGradientRect(float x, float y, float w, float h,
                          float r1, float g1, float b1,
                          float r2, float g2, float b2) {
        glBegin(GL_QUADS);
            glColor3f(r1, g1, b1);
            glVertex2f(x, y + h);
            glVertex2f(x + w, y + h);
            glColor3f(r2, g2, b2);
            glVertex2f(x + w, y);
            glVertex2f(x, y);
        glEnd();
    }

    void drawText(float x, float y, const char* text, float r, float g, float b) {
        glColor3f(r, g, b);
        glRasterPos2f(x, y);
        for (int i = 0; i < (int)strlen(text); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
        }
    }

    void drawTextLarge(float x, float y, const char* text, float r, float g, float b) {
        glColor3f(r, g, b);
        glRasterPos2f(x, y);
        for (int i = 0; i < (int)strlen(text); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }
    }

    void enableBlend() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void disableBlend() {
        glDisable(GL_BLEND);
    }
}
