//
// Created by Bram on 23/08/2024.
//

#ifndef GLOOM_CUBE_H
#define GLOOM_CUBE_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <array>
#include "glad/glad.h"
#include "gloom/Texture.h"
#include "gloom/config.hpp"
#include "Chunk.h"
#include "gloom/Mesh.h"

struct CubeVertex {
    CubeVertex(glm::vec3 pos, glm::vec3 color, glm::vec2 texCoords) : position(pos), color(color),
                                                                      texCoords(texCoords) {};

    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoords;
};


enum Face {
    TOP = 0x01, // 0000 0001
    BOTTOM = 0x02, // 0000 0010
    LEFT = 0x04, // 0000 0100
    RIGHT = 0x08, // 0000 1000
    FRONT = 0x10, // 0001 0000
    BACK = 0x20  // 0010 0000
};


class Cube {
public:
    explicit Cube(const glm::vec3 &position, BlockType blockType);


    static void LoadFace(Face face, std::vector<Mesh::Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec3& position, BlockType type);
    static void LoadAllFaces(std::vector<Mesh::Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec3& position, BlockType type);

    static int faceToIndex(Face face);

    static glm::dvec2 getTexCoords(int pos);

    Mesh* mesh;
private:
    glm::vec3 position;

    Texture texture;
    BlockType type{ BlockType::AIR };
};


#endif //GLOOM_CUBE_H
