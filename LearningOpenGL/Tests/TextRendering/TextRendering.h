#pragma once

#include <map>
#include <conio.h>
#include <Engine.h>

struct Character
{
    unsigned int textureId;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

void textRendering();