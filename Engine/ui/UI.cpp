#include "UI.h"

using namespace ImGui;

UI::UI() {}
UI::~UI() {}

ImGuiIO UI::getIO()
{
    return io;
}

void UI::init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    CreateContext();
    io = GetIO();
    (void)io;

    StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}
void UI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}
void UI::renderFrame()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
void UI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}