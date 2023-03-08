#include "./menuBar.h"

#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_glfw.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"

#include "./moveCamera/moveCamera.h"

bool demo = false;
bool moveCamera = false;

void imGuiMenuBar()
{
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Windows"))
    {
        ImGui::MenuItem("Show demo", NULL, &demo);
        ImGui::MenuItem("Move camera", NULL, &moveCamera);

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if (demo)
        ImGui::ShowDemoWindow();
    if (moveCamera)
        imGuiScreenMoveCamera(&moveCamera);
}