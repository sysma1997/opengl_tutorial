/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "./shader.h"

#include <iostream>

GameShader::GameShader() {}

void GameShader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[512];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 512, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- \n";
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 512, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- \n";
        }
    }
}

GameShader &GameShader::use()
{
    glUseProgram(this->id);
    return *this;
}

void GameShader::compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, sVertex);
    glAttachShader(this->id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->id, gShader);
    glLinkProgram(this->id);
    checkCompileErrors(this->id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void GameShader::setFloat(const char *name, float value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
void GameShader::setInteger(const char *name, int value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void GameShader::setVector2f(const char *name, float x, float y, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void GameShader::setVector2f(const char *name, const glm::vec2 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void GameShader::setVector3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}
void GameShader::setVector3f(const char *name, const glm::vec3 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void GameShader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}
void GameShader::setVector4f(const char *name, const glm::vec4 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void GameShader::setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));
}