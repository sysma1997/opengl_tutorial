#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "UI/UI.h"

class Engine {
public:
    int width;
    int height;
    GLFWwindow* window;

    Engine();
    Engine(int width, int height);
    ~Engine();

    float fWidth();
    float fHeight();

    void init(const char* title, bool is2D = false);
    bool isClose();
    void newFrame();
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};