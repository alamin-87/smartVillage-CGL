#include <GL/glut.h>
#include "app/application.h"
#include <ctime>
#include <cstdlib>

// Window size
int WIDTH = 1000;
int HEIGHT = 700;

// Display callback
void display() {
    Application::getInstance().render();
}

// Update / animation loop
void update(int value) {
    Application::getInstance().update();

    glutPostRedisplay();              // redraw screen
    glutTimerFunc(16, update, 0);     // ~60 FPS
}

// Keyboard input
void keyboard(unsigned char key, int x, int y) {
    Application::getInstance().handleInput(key);
}

// Initialization
void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // sky color
    
    // Enable Visual Quality Enhancements
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}


// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Smart Village Simulation");
    srand(time(NULL));

    init();

    // Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    Application::getInstance().init();

    // Start main loop
    glutMainLoop();

    return 0;
}