//
// Created by Bram on 23/08/2024.
//

#include "Cube.h"

glm::vec3 unitVertices[8] = {
        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)
};


unsigned int faceVertices[6][4] = {
        {3, 2, 6, 7},
        {1, 0, 4, 5},
        {4, 0, 3, 7},
        {1, 5, 6, 2},
        // FRONT (0, 1, 2, 3)
        {0, 1, 2, 3},
        // BACK (5, 4, 7, 6)
        {5, 4, 7, 6}
};

static const glm::vec2 DIRTCOORDS = Cube::getTexCoords(0);
static const glm::vec2 STONECOORDS = Cube::getTexCoords(1);
static const glm::vec2 GONCALOCOORDS = Cube::getTexCoords(2);
static const glm::vec2 GRASSCOORDS = Cube::getTexCoords(3);
static const glm::vec2 SNOWCOORDS = Cube::getTexCoords(4);

Cube::Cube(const glm::vec3 &position, BlockType blockType) : position(position), texture("assets/dirt.png"),
                                                             type(blockType) {
//    setupCube();
}

void Cube::LoadFace(Face face, std::vector<Mesh::Vertex> &vertices, std::vector<unsigned int> &indices, const glm::vec3 &position, BlockType type) {

    glm::vec3 normal;
    switch (face) {
        case Face::TOP:
            normal = glm::vec3(0.0f, 1.0f, 0.0f);
            break;
        case Face::BOTTOM:
            normal = glm::vec3(0.0f, -1.0f, 0.0f);
            break;
        case Face::LEFT:
            normal = glm::vec3(-1.0f, 0.0f, 0.0f);
            break;
        case Face::RIGHT:
            normal = glm::vec3(1.0f, 0.0f, 0.0f);
            break;
        case Face::FRONT:
            normal = glm::vec3(0.0f, 0.0f, 1.0f);
            break;
        case Face::BACK:
            normal = glm::vec3(0.0f, 0.0f, -1.0f);
            break;
    }

    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec2 textureOffset = glm::vec2(0.0f, 0.0f);

    switch(type){
        case BlockType::STONE:
            textureOffset = STONECOORDS;
            break;
        case BlockType::DIRT:
            textureOffset = DIRTCOORDS;
            break;
        case BlockType::GONCALO:
            textureOffset = GONCALOCOORDS;
            break;
        case BlockType::GRASS:
            textureOffset = GRASSCOORDS;
            break;
        case BlockType::SNOW:
            textureOffset = SNOWCOORDS;
            break;
    }

    glm::vec2 uvCoordinates[4] = {
            glm::vec2(textureOffset.x, textureOffset.y + CELL_HEIGHT),
            glm::vec2(textureOffset.x + CELL_WIDTH, textureOffset.y + CELL_HEIGHT),
            glm::vec2(textureOffset.x + CELL_WIDTH, textureOffset.y),
            glm::vec2(textureOffset.x, textureOffset.y)
    };

    unsigned int index = vertices.size();

    for (int i = 0; i < 4; i++) {
        unsigned int vertexIndex = faceVertices[faceToIndex(face)][i];
        Mesh::Vertex v;
        v.position = unitVertices[vertexIndex] + position;
        v.texCoords = uvCoordinates[i];
        vertices.push_back(v);
    }

    indices.push_back(index);
    indices.push_back(index + 1);
    indices.push_back(index + 2);
    indices.push_back(index);
    indices.push_back(index + 2);
    indices.push_back(index + 3);


}

void Cube::LoadAllFaces(std::vector<Mesh::Vertex> &vertices, std::vector<unsigned int> &indices, const glm::vec3 &position, BlockType type) {
    Cube::LoadFace(Face::TOP, vertices, indices, position, type);
    Cube::LoadFace(Face::BOTTOM, vertices, indices, position, type);
    Cube::LoadFace(Face::LEFT, vertices, indices, position, type);
    Cube::LoadFace(Face::RIGHT, vertices, indices, position, type);
    Cube::LoadFace(Face::FRONT, vertices, indices, position, type);
    Cube::LoadFace(Face::BACK, vertices, indices, position, type);
}

int Cube::faceToIndex(Face face) {
    switch (face) {
        case Face::TOP:
            return 0;
        case Face::BOTTOM:
            return 1;
        case Face::LEFT:
            return 2;
        case Face::RIGHT:
            return 3;
        case Face::FRONT:
            return 4;
        case Face::BACK:
            return 5;
    }
}

glm::dvec2 Cube::getTexCoords(int pos) {
    int x = pos % TEXTURE_WIDTH;
    int y = pos / 16;
    return glm::vec2(x * CELL_WIDTH, y * CELL_HEIGHT);
}
