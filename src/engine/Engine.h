#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "./ui/ui.h"
#include "./shader/Shader.h"
#include "./texture/Texture.h"
#include "./model/Model.h"
#include "./2D/Sprite2D.h"
#include "2D/Particle2D.h"
#include "./resourceManager/ResourceManager.h"

#include "./camera/Camera.h"

class Engine
{
private:
    int width;
    int height;
    GLFWwindow *window;

public:
    Engine();
    Engine(int width, int height);
    ~Engine();

    int getWidth();
    int getHeight();
    GLFWwindow *getWindow();

    void init(const char *title, bool is2D = false);
    bool isClose();
    void newFrame();
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};