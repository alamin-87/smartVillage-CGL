#ifndef CLOUD_H
#define CLOUD_H

class Cloud {
public:
    Cloud(float x, float y, float size);
    void update(bool isWindy, bool isStormy);
    void render();

    void setBounds(float min, float max) { minX = min; maxX = max; }

private:
    float posX, posY;
    float scale;
    float speed;
    float minX = -1.3f, maxX = 1.3f;
};

#endif
