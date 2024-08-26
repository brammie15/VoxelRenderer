//
// Created by Bram on 23/08/2024.
//

#ifndef GLOOM_GAME_H
#define GLOOM_GAME_H


#include "GLFW/glfw3.h"
#include "gloom/Shader.h"
#include "Cube.h"
#include "World.h"

static void glfwErrorCallback(int error, const char *description);

class Game {
public:
    Game();
    ~Game();

    void run();
    void handleKeyboard();


private:
    GLFWwindow* m_window;

    bool m_isMouseLocked{ false };

    double m_lastFrameTime{ 0.0 };
    double m_deltaTime{ 0.0 };

    Shader m_shader;

//    Mesh* m_mesh;
//    std::vector<Chunk*> m_chunks;
//    std::vector<Cube> m_cubes;

    World* m_world;
};


#endif //GLOOM_GAME_H
