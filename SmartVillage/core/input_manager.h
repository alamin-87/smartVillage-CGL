#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

// Tracks keyboard state for responsive input handling
class InputManager {
public:
    static InputManager& getInstance();

    void keyPressed(unsigned char key);
    void keyReleased(unsigned char key);

    bool isKeyDown(unsigned char key) const;
    bool isKeyJustPressed(unsigned char key) const;

    // Call at end of each frame to reset per-frame state
    void endFrame();

private:
    InputManager();
    bool keys[256];
    bool keysJustPressed[256];
};

#endif
