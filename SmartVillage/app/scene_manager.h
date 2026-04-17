#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../scene/scene.h"

// Manages scene transitions and tracks which scene is currently active
class SceneManager {
public:
    static SceneManager& getInstance();

    void setScene(int sceneIndex);
    int getCurrentScene() const { return currentScene; }
    const char* getSceneName() const;

    // Scene transition animation
    bool isTransitioning() const { return transitioning; }
    float getTransitionAlpha() const { return transitionAlpha; }
    void update(float dt);

private:
    SceneManager();
    int currentScene;      // 1=Village, 2=Rural, 3=Urban
    bool transitioning;
    float transitionAlpha; // 0.0 = no overlay, 1.0 = full black
    int targetScene;
    float transitionTimer;
};

#endif
