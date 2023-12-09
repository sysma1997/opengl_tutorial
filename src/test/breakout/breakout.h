#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./game/game.h"
#include "./game/utils/resourceManager.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

void breakout();