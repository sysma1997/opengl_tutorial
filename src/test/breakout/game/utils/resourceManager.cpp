/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "./resourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../../../../../libs/stb_image.h"

// Instantiate static variables
std::map<std::string, GameTexture2D> ResourceManager::Textures;
std::map<std::string, GameShader> ResourceManager::Shaders;

GameShader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

GameShader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

GameTexture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = LoadTextureFromFile(file, alpha);
    return Textures[name];
}

GameTexture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.id);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.id);
}

GameShader ResourceManager::LoadShaderFromFile(const char *vShaderFile,
                                               const char *fShaderFile,
                                               const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile, std::ios::in);
        if (!vertexShaderFile.is_open())
            throw "Impossible to open " + std::string(vShaderFile) +
                ". Are you in the right directory? " +
                "Don't forget to read the FAQ!\n";
        std::ifstream fragmentShaderFile(fShaderFile, std::ios::in);
        if (!fragmentShaderFile.is_open())
            throw "Impossible to open " + std::string(fShaderFile) +
                ". Are you in the right directory? " +
                "Don't forget to read the FAQ!\n";
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryCode = gShaderStream.str();
            geometryShaderFile.close();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    GameShader shader;
    shader.compile(vShaderFile, fShaderFile, (gShaderFile != nullptr) ? gShaderFile : nullptr);
    return shader;
}

GameTexture2D ResourceManager::LoadTextureFromFile(const char *file, bool alpha)
{
    // create texture object
    GameTexture2D texture;
    if (alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}