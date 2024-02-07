#include "Shader.h"

using namespace glm;

Shader::Shader() {}
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::stringstream sstr;

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexPath, std::ios::in);
    if (!vertexShaderStream.is_open())
    {
        std::cout << "Impossible to open " << vertexPath << ". Are you in the right directory? Don't "
            << "forget to read the FAQ!\n";

        return;
    }

    sstr << vertexShaderStream.rdbuf();
    vertexShaderCode = sstr.str();
    vertexShaderStream.close();
    sstr.str("");

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragmentPath, std::ios::in);
    if (!fragmentShaderStream.is_open())
    {
        std::cout << "Impossible to open " << fragmentPath << ". Are you in the right directory? Don't "
            << "forget to read the FAQ!\n";

        return;
    }

    sstr << fragmentShaderStream.rdbuf();
    fragmentShaderCode = sstr.str();
    fragmentShaderStream.close();

    GLint success;
    char infoLog[512];

    // COMPILING VERTEX SHADER
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // CHECK VERTEX SAHDER
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cout << "Error to compile shader vertex: " << infoLog << '\n';
    }

    // COMPILING FRAGMENT SHADER
    char const* fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // CHECK FRAGMENT SHADER
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "Error to compile shader fragment:" << infoLog << '\n';
    }

    // LINK THE PROGRAM
    id = glCreateProgram();
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    glLinkProgram(id);

    // CHECK THE PROGRAM
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Error to linking shaders with program: " << infoLog << '\n';
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const std::string& name, GLboolean value, bool useShader) {
    if (useShader) use();
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, GLint value, bool useShader) {
    if (useShader) use();
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, GLfloat value, bool useShader) {
    if (useShader) use();
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, vec2 value, bool useShader) {
    if (useShader) use();
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}
void Shader::setVec3(const std::string& name, vec3 value, bool useShader) {
    if (useShader) use();
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}
void Shader::setVec4(const std::string& name, vec4 value, bool useShader) {
    if (useShader) use();
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}
void Shader::setMat4(const std::string& name, mat4 value, bool useShader) {
    if (useShader) use();
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
}