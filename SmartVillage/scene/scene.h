#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~Scene() {}

    virtual void toggleRain() = 0;
    virtual void toggleStorm() = 0;
    virtual void toggleWind() = 0;
    virtual void setDayNight(bool forceNight) = 0;
};

#endif
