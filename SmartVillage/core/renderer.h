#ifndef RENDERER_H
#define RENDERER_H

// Utility rendering helpers for common OpenGL drawing operations
namespace Renderer {
    // Draw a filled rectangle with given color
    void drawRect(float x, float y, float w, float h, float r, float g, float b);
    
    // Draw a filled rectangle with alpha
    void drawRectAlpha(float x, float y, float w, float h, float r, float g, float b, float a);

    // Draw a gradient rectangle (top color to bottom color)
    void drawGradientRect(float x, float y, float w, float h,
                          float r1, float g1, float b1,
                          float r2, float g2, float b2);

    // Draw text at position using GLUT bitmap font
    void drawText(float x, float y, const char* text, float r, float g, float b);
    
    // Draw text with larger font
    void drawTextLarge(float x, float y, const char* text, float r, float g, float b);

    // Enable/disable transparency blending
    void enableBlend();
    void disableBlend();
}

#endif
