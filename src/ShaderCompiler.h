#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>

GLuint shaderCompiler(const char *vertex_file_path, const char *fragment_file_path);