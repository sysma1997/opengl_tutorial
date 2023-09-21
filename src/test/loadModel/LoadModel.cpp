#include "./LoadModel.h"

using namespace glm;

bool loadModel_pause = false;
bool loadModel_inverted_mouse = false;

void loadModelKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        loadModel_pause = !loadModel_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        loadModel_inverted_mouse = !loadModel_inverted_mouse;
}

void loadModel()
{
}