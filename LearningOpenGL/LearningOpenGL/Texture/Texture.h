#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture
{
public:
    GLuint id;
    unsigned int width;
    unsigned int height;

    Texture();
    Texture(const char* path, bool rgba = false);
    ~Texture();

    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind() const;

    static void Init();
};