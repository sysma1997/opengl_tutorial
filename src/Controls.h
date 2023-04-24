#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./imguiScreens/moveCamera/moveCamera.h"

void computeMatricesFromInputs(GLFWwindow *window, int width, int height);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();