//
// Created by Bram on 23/08/2024.
//

#include "Mesh.h"
#include "glad/glad.h"
#include "config.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TextureManager.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
    VAOSIZE = 0;
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;
    m_texture = TextureManager::GetInstance().getTexture("assets/dirt.png");
    setupMesh();
}

void Mesh::draw(GLuint shaderID) {

    glUseProgram(shaderID);

    GLuint modelLoc = glGetUniformLocation(shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, m_scale);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    glBindVertexArray(VAO);

    if(renderWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    m_texture->bind(0);

    //Get error
    glDrawElements(GL_TRIANGLES, VAOSIZE, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

void Mesh::setupMesh() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // vertex texture coords
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Free memory
    VAOSIZE = indices.size();  // Now using the size of the indices
}
