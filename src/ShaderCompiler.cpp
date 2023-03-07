#include "ShaderCompiler.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

GLuint shaderCompiler(const char *vertex_file_path, const char *fragment_file_path)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::stringstream sstr;

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
    if (!vertexShaderStream.is_open())
    {
        std::cout << "Impossible to open " << vertex_file_path << ". Are you in the right directory? Don't forget to read the FAQ!" << std::endl;

        return 0;
    }

    sstr << vertexShaderStream.rdbuf();
    vertexShaderCode = sstr.str();
    vertexShaderStream.close();
    sstr.str("");

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if (!fragmentShaderStream.is_open())
    {
        std::cout << "Impossible to open " << fragment_file_path << ". Are you in the right directory? Don't forget to read the FAQ!" << std::endl;

        return 0;
    }

    sstr << fragmentShaderStream.rdbuf();
    fragmentShaderCode = sstr.str();
    fragmentShaderStream.close();

    GLint result = GL_FALSE;
    int infoLogLength;

    // COMPILING VERTEX SHADER
    std::cout << "Compiling shader: " << vertex_file_path << std::endl;
    char const *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // CHECK VERTEX SAHDER
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        std::cout << &vertexShaderErrorMessage[0] << std::endl;
    }

    // COMPILING FRAGMENT SHADER
    std::cout << "Compiling shader: " << fragment_file_path << std::endl;
    char const *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // CHECK FRAGMENT SHADER
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cout << &fragmentShaderErrorMessage[0] << std::endl;
    }

    // LINK THE PROGRAM
    std::cout << "Linking program" << std::endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // CHECK THE PROGRAM
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cout << &programErrorMessage[0] << std::endl;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}