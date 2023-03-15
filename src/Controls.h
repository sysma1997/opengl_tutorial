#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void computeMatricesFromInputs(GLFWwindow *window, int width, int height);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();