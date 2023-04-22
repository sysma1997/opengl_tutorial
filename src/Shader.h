#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
    GLuint id;

    Shader(const char *vertexPath, const char *fragmentPath);

    void use();

    void setBool(const std::string &name, GLboolean value) const;
    void setInt(const std::string &name, GLint value) const;
    void setFloat(const std::string &name, GLfloat value) const;
};