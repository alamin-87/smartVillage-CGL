#ifndef MARKET_H
#define MARKET_H

class Market {
public:
    Market(float x, float y);
    void render(bool isNight);
    void update(float dt);

private:
    float posX, posY;
    float vendorBob;
    void drawStall(float x, float y, float r, float g, float b);
    void drawSign();
    void drawVendor(float x, float y);
};

#endif
