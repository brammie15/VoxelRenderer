////
//// Created by Bram on 23/08/2024.
////
//
//#include "Cube.h"
//
//glm::vec3 unitVertices[8] = {
//        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
//        glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
//        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)
//};
//
//unsigned int faceVertices[6][6] = {
//        // TOP (3, 2, 6, 3, 6, 7)
//        {3, 2, 6, 3, 6, 7},
//        // BOTTOM (1, 0, 4, 1, 4, 5)
//        {1, 0, 4, 1, 4, 5},
//        // LEFT (0, 3, 7, 0, 7, 4)
//        {0, 3, 7, 0, 7, 4},
//        // RIGHT (2, 1, 5, 2, 5, 6)
//        {2, 1, 5, 2, 5, 6},
//        // FRONT (0, 1, 2, 0, 2, 3)
//        {0, 1, 2, 0, 2, 3},
//        // BACK (5, 4, 7, 5, 7, 6)
//        {5, 4, 7, 5, 7, 6}
//};
//
//
//void Cube::Draw(GLuint shaderProgram) {
//    // Use the shader program
//    glUseProgram(shaderProgram);
//
//    // Transform the cube
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    if(renderWireframe) {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    } else {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    }
//
//    // Draw the cube
//    texture.bind(0);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//
//}
//
//void Cube::setupCube() {
//
//
//
//
//    std::array<CubeVertex, 24> cubeVertices = {
//            // Front face (z = 1.0f)
//            CubeVertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // Top-left
//
//            // Back face (z = -1.0f)
//            CubeVertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)), // Top-left
//
//            // Left face (x = -1.0f)
//            CubeVertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // Top-left
//
//            // Right face (x = 1.0f)
//            CubeVertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f)), // Top-left
//
//            // Bottom face (y = -1.0f)
//            CubeVertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // Top-left
//
//            // Top face (y = 1.0f)
//            CubeVertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
//            CubeVertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // Bottom-right
//            CubeVertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // Top-right
//            CubeVertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f))  // Top-left
//    };
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices.data(), GL_STATIC_DRAW);
//
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices.data(), GL_STATIC_DRAW);
//
//
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void *) offsetof(CubeVertex, position));
//    glEnableVertexAttribArray(0);
//
//    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void *) offsetof(CubeVertex, color));
//    glEnableVertexAttribArray(1);
//
//    // Texture Coords
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void *) offsetof(CubeVertex, texCoords));
//    glEnableVertexAttribArray(2);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//Cube::Cube(const glm::vec3 &position, BlockType blockType): position(position), texture("assets/dirt.png"), type(blockType) {
//    setupCube();
//}
//
//void Cube::LoadFace(Face face, std::vector<CubeVertex> &vertices) {
//
//    glm::vec3 normal;
//    switch (face) {
//        case Face::TOP:
//            normal = glm::vec3(0.0f, 1.0f, 0.0f);
//            break;
//        case Face::BOTTOM:
//            normal = glm::vec3(0.0f, -1.0f, 0.0f);
//            break;
//        case Face::LEFT:
//            normal = glm::vec3(-1.0f, 0.0f, 0.0f);
//            break;
//        case Face::RIGHT:
//            normal = glm::vec3(1.0f, 0.0f, 0.0f);
//            break;
//        case Face::FRONT:
//            normal = glm::vec3(0.0f, 0.0f, 1.0f);
//            break;
//        case Face::BACK:
//            normal = glm::vec3(0.0f, 0.0f, -1.0f);
//            break;
//    }
//
//    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
//    glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);
//
//    for (int i = 0; i < 6; i++) {
//        CubeVertex vertex = {
//                unitVertices[faceVertices[face][i]],
//                color,
//                texCoords
//        };
//        vertices.push_back(vertex);
//    }
//
//}
//
//void Cube::LoadAllFaces(std::vector<CubeVertex> &vertices) {
//    LoadFace(Face::TOP, vertices);
//    LoadFace(Face::BOTTOM, vertices);
//    LoadFace(Face::LEFT, vertices);
//    LoadFace(Face::RIGHT, vertices);
//    LoadFace(Face::FRONT, vertices);
//    LoadFace(Face::BACK, vertices);
//}
