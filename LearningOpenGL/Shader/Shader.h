#pragma once
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    GLuint id;

    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string& name, GLboolean value, bool useShader = false);
    void setInt(const std::string& name, GLint value, bool useShader = false);
    void setFloat(const std::string& name, GLfloat value, bool useShader = false);

    void setVec2(const std::string& name, glm::vec2 value, bool useShader = false);
    void setVec3(const std::string& name, glm::vec3 value, bool useShader = false);
    void setVec4(const std::string& name, glm::vec4 value, bool useShader = false);
    void setMat4(const std::string& name, glm::mat4 value, bool useShader = false);
};