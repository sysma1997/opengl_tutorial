#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

class ResourceManager
{
private:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

public:
    ResourceManager();
    ~ResourceManager();

    static Shader LoadShader(const char* vertexPath, const char* framePath, std::string name);
    static Shader GetShader(std::string name);

    static Texture LoadTexture(const char* texturePath, bool alpha, std::string name);
    static Texture GetTexture(std::string name);

    static void Clear();
};