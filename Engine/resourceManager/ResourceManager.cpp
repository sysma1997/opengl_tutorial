#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

Shader ResourceManager::LoadShader(const char* vertexPath,
    const char* fragmentPath,
    std::string name)
{
    shaders[name] = Shader(vertexPath, fragmentPath);

    return shaders[name];
}
Shader ResourceManager::GetShader(std::string name)
{
    return shaders[name];
}

Texture ResourceManager::LoadTexture(const char* texturePath,
    bool alpha,
    std::string name)
{
    textures[name] = Texture(texturePath, alpha);

    return textures[name];
}
Texture ResourceManager::GetTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::Clear()
{
    for (auto shader : shaders)
        glDeleteProgram(shader.second.id);
    for (auto texture : textures)
    {
        GLuint id{ texture.second.getId() };
        glDeleteTextures(1, &id);
    }
}