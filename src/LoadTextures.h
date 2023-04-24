#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <cstring>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../libs/stb_image.h"

GLuint LoadTexture(const char *image_path);
GLuint LoadTextureDDS(const char *image_path);