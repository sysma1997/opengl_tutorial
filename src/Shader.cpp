#include "./Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::stringstream sstr;

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexPath, std::ios::in);
    if (!vertexShaderStream.is_open())
    {
        std::cout << "Impossible to open " << vertexPath << ". Are you in the right directory? Don't forget to read the FAQ!" << std::endl;

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
        std::cout << "Impossible to open " << fragmentPath << ". Are you in the right directory? Don't forget to read the FAQ!" << std::endl;

        return;
    }

    sstr << fragmentShaderStream.rdbuf();
    fragmentShaderCode = sstr.str();
    fragmentShaderStream.close();

    GLint success;
    char infoLog[512];

    // COMPILING VERTEX SHADER
    std::cout << "Compiling shader: " << vertexPath << std::endl;
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
    std::cout << "Compiling shader: " << fragmentPath << std::endl;
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
    id = glCreateProgram();
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    glLinkProgram(id);

    // CHECK THE PROGRAM
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Error to linking shaders with program: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, GLboolean value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, GLint value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, GLfloat value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}