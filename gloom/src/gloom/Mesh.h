//
// Created by Bram on 23/08/2024.
//

#ifndef GLOOM_MESH_H
#define GLOOM_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include "glad/glad.h"
#include "Texture.h"

class Mesh {
public:
    struct Vertex{
        glm::vec3 position;
        glm::dvec2 texCoords;
    };

    Mesh();
    ~Mesh();
    Mesh(const std::vector<Mesh::Vertex>& vertices, const std::vector<unsigned int>& indices);


    void draw(GLuint shaderID);
    void setupMesh();

    void setPosition(glm::vec3 position) { m_position = position; }
    void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
    void setScale(glm::vec3 scale) { m_scale = scale; }
private:
    unsigned int VAO, VBO, EBO, VAOSIZE;

    glm::vec3 m_position{ 0.0f, -5.0f, 0.0f };
    glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f };
    glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };


    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Texture* m_texture{ nullptr };
};


#endif //GLOOM_MESH_H
