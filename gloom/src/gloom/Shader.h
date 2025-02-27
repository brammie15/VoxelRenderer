//
// Created by Bram on 23/08/2024.
//

#ifndef GLOOM_SHADER_H
#define GLOOM_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int ID;
    Shader();

    void use();
    void setShader(const char* vertexPath, const char* fragmentPath);

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;


    //shadow map
    unsigned int depthMapFBO, depthMap;
    int shadowWidth = 4096, shadowHeight = 4096; // Adjust the size as needed
    void setupShadowMap();
    void renderShadowMap(glm::mat4 lightSpaceMatrix);
};
#endif //GLOOM_SHADER_H
