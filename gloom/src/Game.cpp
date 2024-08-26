//
// Created by Bram on 23/08/2024.
//

#include "Game.h"
#include "gloom/config.hpp"
#include "gloom/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// A callback which allows GLFW to report errors whenever they occur
static void glfwErrorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW returned an error:\n\t%s (%i)\n", description, error);
}

static void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    glm::vec2 mousePos((float) xpos, (float) -ypos);

    Camera::getInstance().updateMouse(mousePos);

}

Game::Game() {
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Could not start GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Set core window options (adjust version numbers if needed)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable the GLFW runtime error callback function defined previously.
    glfwSetErrorCallback(glfwErrorCallback);
    // We to good for errors

    // Set additional window options
    glfwWindowHint(GLFW_RESIZABLE, windowResizable);
//    glfwWindowHint(GLFW_SAMPLES, windowSamples);  // MSAA

//    glDisable(GL_MULTISAMPLE);

    // Create window using GLFW
    m_window = glfwCreateWindow(windowWidth,
                                windowHeight,
                                windowTitle.c_str(),
                                nullptr,
                                nullptr);

    // Ensure the window is set up correctly
    if (!m_window) {
        fprintf(stderr, "Could not open GLFW window\n");
        //Get the error and print it
        const char *description;
        int error = glfwGetError(&description);
        fprintf(stderr, "Error: %s\n", description);

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Let the window be the current OpenGL context and initialise glad
    glfwMakeContextCurrent(m_window);
    gladLoadGL();

    // Print various OpenGL information to stdout
    printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    printf("GLFW\t %s\n", glfwGetVersionString());
    printf("OpenGL\t %s\n", glGetString(GL_VERSION));
    printf("GLSL\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Set up the mouse callback
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window, mouse_callback);

    // Set up the shader
    m_shader.setShader("shaders/simple.vert", "shaders/simple.frag");

    // Set up the block
//    // 16 x 16
//    for (int x = 0; x < CHUNK_SIZE; x+=1) {
//        for(int y = 0; y < CHUNK_HEIGHT / 4; y+=1) {
//            for (int z = 0; z < CHUNK_SIZE; z+=1) {
//                BlockType type = static_cast<BlockType>(rand() % 3);
//                m_cubes.emplace_back(glm::vec3(x, y, z), type);
//            }
//        }
//    }


//    //10 x 10 chunk
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            m_chunks.push_back(new Chunk(glm::vec2(i, j)));
//            m_chunks[m_chunks.size() - 1]->loadBlocks();
//            m_chunks[m_chunks.size() - 1]->loadMesh();
//        }
//    }

    m_world = &World::GetInstance();
    m_world->generateChunk(0, 0);
//    m_world->generateChunk(1, 0);
//    m_world->getChunk(0, 0)->loadMesh();
//    m_world->generateChunk(0, 1);
//    m_world->generateChunk(1, 1);
//    m_world->getChunk(1, 0)->loadMesh();





}

Game::~Game() {
    glfwTerminate();
}

void Game::run() {
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
//    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    double lastChunkUpdate = glfwGetTime();

    // Set up your scene here (create Vertex Array Objects, etc.)

    // Rendering Loop
    while (!glfwWindowShouldClose(this->m_window)) {

        // Calculate delta time
        double currentTime = glfwGetTime();
        m_deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

//        // wait until next frame with fps
//        while (glfwGetTime() - m_lastFrameTime < 1.0 / MAX_FPS) {
//        }



        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here

        // Set the shader program
        m_shader.use();
        glViewport(0, 0, windowWidth, windowHeight);

        m_shader.setMat4("view", Camera::getInstance().getViewMatrix());
        m_shader.setMat4("projection", Camera::getInstance().projectionMatrix);


//        for (auto &chunk: m_chunks) {
//            chunk->Draw(m_shader.ID);
//        }
//
        m_world->Draw(m_shader.ID, Camera::getInstance().camPos);
//
//        // if player is above chunk that is not generated, generate it, add a variance of the renderdistance
        int playerX = (int) Camera::getInstance().camPos.x / CHUNK_SIZE;
        int playerZ = (int) Camera::getInstance().camPos.z / CHUNK_SIZE;

        if(glfwGetTime() - lastChunkUpdate > 0.5) {
            lastChunkUpdate = glfwGetTime();
            for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
                for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
                    if (m_world->isChunkGenerated(x,z) == ChunkLoadStatus::NOT_GENERATED) {
                        m_world->generateChunk(x, z);
                        //Now take the 4 chunks next to it and update those
    //
                        if (m_world->isChunkGenerated(x + 1, z) == ChunkLoadStatus::GENERATED) {
                            m_world->getChunk(x + 1, z)->loadMesh();
                        }
                        if (m_world->isChunkGenerated(x - 1, z) == ChunkLoadStatus::GENERATED) {
                            m_world->getChunk(x - 1, z)->loadMesh();
                        }
                        if (m_world->isChunkGenerated(x, z + 1) == ChunkLoadStatus::GENERATED) {
                            m_world->getChunk(x, z + 1)->loadMesh();
                        }
                        if (m_world->isChunkGenerated(x, z - 1) == ChunkLoadStatus::GENERATED) {
                            m_world->getChunk(x, z - 1)->loadMesh();
                        }
                    }
                }
            }
        }
//

        // Handle other events
        glfwPollEvents();
        this->handleKeyboard();

        // Flip buffers
        glfwSwapBuffers(this->m_window);
    }

}

void Game::handleKeyboard() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    glm::vec3 moveDir(0, 0, 0);

    //movement
    if (glfwGetKey(this->m_window, GLFW_KEY_W) == GLFW_PRESS)
        moveDir.z -= 1; // Move forward
    if (glfwGetKey(this->m_window, GLFW_KEY_S) == GLFW_PRESS)
        moveDir.z += 1; // Move backward
    if (glfwGetKey(this->m_window, GLFW_KEY_A) == GLFW_PRESS)
        moveDir.x -= 1; // Move left
    if (glfwGetKey(this->m_window, GLFW_KEY_D) == GLFW_PRESS)
        moveDir.x += 1; // Move right
    if (glfwGetKey(this->m_window, GLFW_KEY_E) == GLFW_PRESS)
        moveDir.y += 1;
    if (glfwGetKey(this->m_window, GLFW_KEY_Q) == GLFW_PRESS)
        moveDir.y -= 1;

    if (length(moveDir) > 0)
        Camera::getInstance().updatePos(normalize(moveDir), m_deltaTime);

    static bool lastR = false; //Kinda shitty but damm i could not care less
    if (glfwGetKey(this->m_window, GLFW_KEY_R) == GLFW_PRESS && !lastR) {
        renderWireframe = !renderWireframe;
        lastR = true;
    } else if (glfwGetKey(this->m_window, GLFW_KEY_R) == GLFW_RELEASE) {
        lastR = false;
    }

    //unlock mouse
    static bool keyWasPressed = false;
    if (glfwGetKey(this->m_window, GLFW_KEY_T) == GLFW_PRESS) {
        if (!keyWasPressed) {
            m_isMouseLocked = !m_isMouseLocked; // Toggle the state
            glfwSetInputMode(this->m_window, GLFW_CURSOR, m_isMouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            keyWasPressed = true;
        }
    } else {
        keyWasPressed = false;
    }


    static bool balls = false;
    if (glfwGetKey(this->m_window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!balls) {
            //Random number between 1234u and 500u
            SEED = rand() * 10000u;
            perlin = siv::PerlinNoise(SEED);
            m_world->generateChunk(1, 0);
            m_world->generateChunk(0, 1);
            m_world->generateChunk(0, 0);
            m_world->generateChunk(1, 1);
            std::cout << "Seed: " << SEED << std::endl;
            balls = true;
        }
    } else {
        balls = false;
    }

}
