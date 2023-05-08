#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture
{
private:
    GLuint id;

public:
    Texture(const char *path, bool rgba = false);
    ~Texture();

    GLuint getId();

    static void Init();
};