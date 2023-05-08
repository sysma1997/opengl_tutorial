#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Texture
{
    void init();
    GLuint loadTexture(const char *path, bool rgba = false);
};