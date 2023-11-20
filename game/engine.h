#ifndef GAME_PROJECT_ENGINE_H
#define GAME_PROJECT_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

class Engine {
    private:
        GLFWwindow *window;
        int rowClick; // Row that was clicked.
        int colClick; // Column that was clicked.

        int cols; // Amount of columns.
        int rows; // AMount of rows.

        void processInput(); // Processes w.
        void render(); // Renders the grid for the game.
        vector<glm::vec2> getNeighbors(); // Get the neighbors of a cell.

    public:
        Engine();
        ~Engine();

        void run(); // Runs the main engine loop.
};


#endif //GAME_PROJECT_ENGINE_H
