#include "scene_manager.h"

SceneManager::SceneManager() {
    currentScene = 1;
    transitioning = false;
    transitionAlpha = 0.0f;
    targetScene = 1;
    transitionTimer = 0.0f;
}

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::setScene(int sceneIndex) {
    if (sceneIndex < 1 || sceneIndex > 3) return;
    if (sceneIndex == currentScene) return;

    targetScene = sceneIndex;
    transitioning = true;
    transitionTimer = 0.0f;
}

const char* SceneManager::getSceneName() const {
    switch (currentScene) {
        case 1: return "MAIN VILLAGE";
        case 2: return "RURAL HOMESTEAD";
        case 3: return "URBAN DISTRICT";
        default: return "UNKNOWN";
    }
}

void SceneManager::update(float dt) {
    if (!transitioning) return;

    transitionTimer += dt * 3.0f; // Speed of transition

    if (transitionTimer < 1.0f) {
        // Fade out
        transitionAlpha = transitionTimer;
    } else if (transitionTimer < 1.1f) {
        // Switch scene at peak
        currentScene = targetScene;
        transitionAlpha = 1.0f;
    } else if (transitionTimer < 2.0f) {
        // Fade in
        transitionAlpha = 2.0f - transitionTimer;
    } else {
        // Done
        transitioning = false;
        transitionAlpha = 0.0f;
    }
}
