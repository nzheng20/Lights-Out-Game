#include "engine.h"
#include <iostream>

using namespace std;

Engine::Engine() {
    // Initializing as -1 to mark it as unclicked.
    rowClick = -1;
    colClick = -1;

    cols = 5;
    rows = 5;

    if (!glfwInit()) {
        cerr << "Failed to init GLFW." << endl;
        exit(-1);
    }

    // Create game window
    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(800, 800, "Lights out", NULL, NULL);

    if (!window) {
        cerr << "Failed to create window." << endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to init GLAD." << endl;
        exit(-1);
    }

    glEnable(GL_BLEND);
}

Engine::~Engine() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::processInput() {
    // Close window if ESC is pressed.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Set col/row clicked when mouse is pressed on grid.
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        colClick = static_cast<int>(mouseX / (800.0 / cols));
        rowClick = static_cast<int>((800.0 - mouseY) / (800.0 / rows));
    }
}

void Engine::render() {
    // Clear color buffer to reset.
    glClear(GL_COLOR_BUFFER_BIT);

    // Setup to use OpenGL projection matrix.
    // https://learn.microsoft.com/en-us/windows/win32/opengl/glmatrixmode
    // Used in order to render on a 2D plane.
    glMatrixMode(GL_PROJECTION);

    // Resets the projection matrix.
    glLoadIdentity();

    // Setting up the 2D coordinate system.
    // https://learn.microsoft.com/en-us/windows/win32/opengl/glortho
    glOrtho(0.0f, cols, 0.0f, rows, -1.0f, 1.0f);
    // left right bottom, etc..

    // Changing to Model view matrix to transform on objects relative to us.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the grid using white lines.
    glColor3f(1.0f, 1.0f, 1.0f);

    // Drawing the lines of the grid.
    glBegin(GL_LINES);

    // Horizontal.
    for (int row = 0; row <= rows; row++) {
        glVertex2f(0.0f, static_cast<float>(row));
        glVertex2f(cols, static_cast<float>(row));
    }

    // Vertical.
    for (int col = 0; col <= cols; col++) {
        glVertex2f(static_cast<float>(col), 0.0f);
        glVertex2f(static_cast<float>(col), rows);
    }

    glEnd();

    // If row and col is clicked draw it as yellow.
    if (rowClick != -1 && colClick != -1) {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow.

        // Draw a square where the cell of the grid is.

        // Casting int to float in order to draw the full square.
        float fcolClick = static_cast<float>(colClick);
        float frowClick = static_cast<float>(rowClick);

        glBegin(GL_QUADS);
        glVertex2f(fcolClick, frowClick);
        glVertex2f(fcolClick + 1, frowClick);
        glVertex2f(fcolClick + 1, frowClick + 1);
        glVertex2f(fcolClick, frowClick + 1);
        glEnd();
    }
}

vector<glm::vec2> Engine::getNeighbors() {
    // Vector of neighboring cells.
    vector<glm::vec2> neighbors;

    // Positions of neighbors relative to the current cell. This will be in eight directions.
    const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int i = 0; i < 8; i++) {
        int nCol = colClick + dx[i];
        int nRow = rowClick + dy[i];

        // Check if neighbor is within the grid,
        if (nCol >= 0 && nCol < cols && nRow >= 0 && nRow < rows) {
            neighbors.push_back(glm::vec2(nCol, nRow));
        }
    }

    return neighbors;
}

