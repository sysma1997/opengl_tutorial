#include "ShaderCompiler.h"

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

    GLint success;
    char infoLog[512];

    // COMPILING VERTEX SHADER
    std::cout << "Compiling shader: " << vertex_file_path << std::endl;
    char const *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // CHECK VERTEX SAHDER
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cout << "Error to compile shader vertex: " << infoLog << std::endl;
    }

    // COMPILING FRAGMENT SHADER
    std::cout << "Compiling shader: " << fragment_file_path << std::endl;
    char const *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // CHECK FRAGMENT SHADER
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "Error to compile shader fragment:" << infoLog << std::endl;
    }

    // LINK THE PROGRAM
    std::cout << "Linking program" << std::endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // CHECK THE PROGRAM
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "Error to linking shaders with program: " << infoLog << std::endl;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}