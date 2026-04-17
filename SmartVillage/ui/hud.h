#ifndef HUD_H
#define HUD_H

class HUD {
public:
    void render(float sunAngle, bool isRainy, bool isStormy, bool isWindy);

private:
    void drawText(float x, float y, const char* text);
};

#endif
