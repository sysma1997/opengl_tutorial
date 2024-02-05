#pragma once

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

class UI
{
private:
    ImGuiIO io;

public:
    UI();
    ~UI();

    ImGuiIO getIO();

    void init(GLFWwindow* window);
    void newFrame();
    void renderFrame();
    void terminate();
};