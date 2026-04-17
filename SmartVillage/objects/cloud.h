#ifndef CLOUD_H
#define CLOUD_H

class Cloud {
public:
    Cloud(float x, float y, float size);
    void update(bool isWindy, bool isStormy);
    void render();

private:
    float posX, posY;
    float scale;
    float speed;
};

#endif
