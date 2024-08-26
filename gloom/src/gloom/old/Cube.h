////
//// Created by Bram on 23/08/2024.
////
//
//#ifndef GLOOM_CUBE_H
//#define GLOOM_CUBE_H
//
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <vector>
//#include <iostream>
//#include <array>
//#include "glad/glad.h"
//#include "gloom/Texture.h"
//#include "gloom/config.hpp"
//#include "Chunk.h"
//#include "gloom/Mesh.h"
//
//struct CubeVertex {
//    CubeVertex(glm::vec3 pos, glm::vec3 color, glm::vec2 texCoords) : position(pos), color(color),
//                                                                      texCoords(texCoords) {};
//
//    glm::vec3 position;
//    glm::vec3 color;
//    glm::vec2 texCoords;
//};
//
//struct CubeFace {
//};
//
//static std::array<unsigned int, 36> cubeIndices = {
//        // Front face
//        0, 1, 2,  // First triangle (0, 1, 2)
//        0, 2, 3,  // Second triangle (0, 2, 3)
//
//        // Back face
//        4, 5, 6,  // First triangle (4, 5, 6)
//        4, 6, 7,  // Second triangle (4, 6, 7)
//
//        // Left face
//        8, 9, 10, // First triangle (8, 9, 10)
//        8, 10, 11,// Second triangle (8, 10, 11)
//
//        // Right face
//        12, 13, 14,// First triangle (12, 13, 14)
//        12, 14, 15,// Second triangle (12, 14, 15)
//
//        // Bottom face
//        16, 17, 18,// First triangle (16, 17, 18)
//        16, 18, 19,// Second triangle (16, 18, 19)
//
//        // Top face
//        20, 21, 22,// First triangle (20, 21, 22)
//        20, 22, 23 // Second triangle (20, 22, 23)
//};
//
//enum Face {
//    TOP = 0x01, // 0000 0001
//    BOTTOM = 0x02, // 0000 0010
//    LEFT = 0x04, // 0000 0100
//    RIGHT = 0x08, // 0000 1000
//    FRONT = 0x10, // 0001 0000
//    BACK = 0x20  // 0010 0000
//};
//
//
//class Cube {
//public:
//    explicit Cube(const glm::vec3 &position, BlockType blockType);
//
//    void Draw(GLuint shaderProgram);
//
//    void LoadFace(Face face, std::vector<CubeVertex>& vertices);
//    void LoadAllFaces(std::vector<CubeVertex>& vertices);
//
//    Mesh mesh;
//private:
//    GLuint VAO{}, VBO{}, EBO{};
//    glm::vec3 position;
//
//    Texture texture;
//    BlockType type{ BlockType::AIR };
//    void setupCube();
//};
//
//
//#endif //GLOOM_CUBE_H
