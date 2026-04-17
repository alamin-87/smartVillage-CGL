#ifndef TREE_H
#define TREE_H

class Tree {
public:
    Tree(float x, float y);

    void update(bool isWindy);
    void render();

private:
    float posX, posY;
    float angle;     // for animation
};

#endif