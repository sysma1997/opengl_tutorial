#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

bool LoadModelObj(const char *model_path,
                  std::vector<glm::vec3> &out_vertices,
                  std::vector<glm::vec2> &out_uvs,
                  std::vector<glm::vec3> &out_normals);