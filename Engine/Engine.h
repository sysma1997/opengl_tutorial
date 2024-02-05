#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "shader/Shader.h"
#include "texture/Texture.h"
#include "model/Model.h"
#include "2D/Sprite2D.h"
#include "2D/Particle2D.h"
#include "resourceManager/ResourceManager.h"
#include "camera/Camera.h"
#include "ui/UI.h"

class Engine
{
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
