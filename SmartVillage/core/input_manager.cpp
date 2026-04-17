#include "input_manager.h"
#include <cstring>

InputManager::InputManager() {
    memset(keys, false, sizeof(keys));
    memset(keysJustPressed, false, sizeof(keysJustPressed));
}

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::keyPressed(unsigned char key) {
    if (!keys[key]) {
        keysJustPressed[key] = true;
    }
    keys[key] = true;
}

void InputManager::keyReleased(unsigned char key) {
    keys[key] = false;
}

bool InputManager::isKeyDown(unsigned char key) const {
    return keys[key];
}

bool InputManager::isKeyJustPressed(unsigned char key) const {
    return keysJustPressed[key];
}

void InputManager::endFrame() {
    memset(keysJustPressed, false, sizeof(keysJustPressed));
}
