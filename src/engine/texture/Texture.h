#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture
{
private:
    GLuint id;

public:
    unsigned int width;
    unsigned int height;

    Texture();
    Texture(const char *path, bool rgba = false);
    ~Texture();

    GLuint getId();

    static void Init();
};