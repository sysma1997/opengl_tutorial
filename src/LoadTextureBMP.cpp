#include "LoadTextureBMP.h"

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

GLuint LoadTextureBMP(const char *image_path)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;

    unsigned char *data;

    FILE *file = fopen(image_path, "rb");
    if (!file)
    {
        std::cout << "Image could not be opened" << std::endl;

        return 0;
    }
}