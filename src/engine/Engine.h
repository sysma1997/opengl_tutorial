#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_glfw.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"
#include "../../libs/stb_image.h"

#include "./shader/Shader.h"

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

    void init(const char *title);
    bool isClose();
    void newFrame();
    void renderFrame();
    void terminate();

    void setKeyCallback(GLFWkeyfun callback);
};