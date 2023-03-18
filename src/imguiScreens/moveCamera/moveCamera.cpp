#include "./moveCamera.h"

#include <string>
#include <glm/glm.hpp>

#include "../../../libs/imgui/imgui.h"
#include "../../../libs/imgui/imgui_impl_glfw.h"
#include "../../../libs/imgui/imgui_impl_opengl3.h"

/* PROJECTION VARIABLES */
const char *GMoveCamera::PROJECTION_TYPES[2] = {"Matrix", "Ortho"};
int GMoveCamera::projection_type_index = 0;

float GMoveCamera::projection_field_of_view = 45.0f;

float GMoveCamera::PROJECTION_RATIO_4_3 = 800.0f / 480.0f;
float GMoveCamera::PROJECTION_RATIO_5_4 = 1280.0f / 1024.0f;
float GMoveCamera::PROJECTION_RATIO_16_9 = 1366.0f / 768.0f;
const char *GMoveCamera::PROJECTION_RATIOS[3] = {"4:3", "5:4", "16:9"};
const float GMoveCamera::PROJECTION_RATIOS_VALUES[3] = {GMoveCamera::PROJECTION_RATIO_4_3,
                                                        GMoveCamera::PROJECTION_RATIO_5_4,
                                                        GMoveCamera::PROJECTION_RATIO_16_9};
int GMoveCamera::projection_ratio_index = 0;

float GMoveCamera::projection_unit_init = 0.1f;
float GMoveCamera::projection_unit_end = 100.0f;
/* END PROJECTION VARIABLES */

/* VIEW VARIABLES */
glm::vec3 GMoveCamera::work_space(4.0f, 3.0f, 3.0f);
glm::vec3 GMoveCamera::view_center(0.0f, 0.0f, 0.0f);
glm::vec3 GMoveCamera::view_up(0.0f, 1.0f, 0.0f);
/* END VIEW VARIABLES */

bool GMoveCamera::pause = false;

void imGuiScreenMoveCamera(bool *open)
{
    ImGui::Begin("Camera", open);

    /* PERSPECTIVE */
    ImGui::Text("PERSPECTIVE");
    ImGui::NewLine();
    ImGui::Text("Type projection:");
    const char *type_projection_preview_value = GMoveCamera::PROJECTION_TYPES[GMoveCamera::projection_type_index];
    if (ImGui::BeginCombo("##type_projection", type_projection_preview_value))
    {
        for (int i = 0; i < IM_ARRAYSIZE(GMoveCamera::PROJECTION_TYPES); i++)
        {
            const bool is_selected = (i == GMoveCamera::projection_type_index);
            if (ImGui::Selectable(GMoveCamera::PROJECTION_TYPES[i], is_selected))
                GMoveCamera::projection_type_index = i;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (GMoveCamera::projection_type_index == 0)
    {
        ImGui::Text("Field of view:");
        ImGui::SliderFloat("##projection_field_of_view", &GMoveCamera::projection_field_of_view, 15.0f, 80.0f);

        ImGui::Text("Ratio:");
        const char *ratio_preview_value = GMoveCamera::PROJECTION_RATIOS[GMoveCamera::projection_ratio_index];
        if (ImGui::BeginCombo("##ratio", ratio_preview_value))
        {
            for (int i = 0; i < IM_ARRAYSIZE(GMoveCamera::PROJECTION_RATIOS); i++)
            {
                const bool is_selected = (i == GMoveCamera::projection_ratio_index);
                if (ImGui::Selectable(GMoveCamera::PROJECTION_RATIOS[i], is_selected))
                    GMoveCamera::projection_ratio_index = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::Text("Units:");
        ImGui::Text("Unit init");
        ImGui::SameLine();
        ImGui::InputFloat("##projection_unit_init", &GMoveCamera::projection_unit_init);
        ImGui::Text("Unit end");
        ImGui::SameLine();
        ImGui::InputFloat("##projection_unit_end", &GMoveCamera::projection_unit_end);
    }
    /* END PERSPECTIVE */

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    /* VIEW */
    ImGui::Text("VIEW");
    ImGui::NewLine();

    ImGui::Text("Work space (Position):");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::InputFloat("##eye x", &GMoveCamera::work_space.x);
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::InputFloat("##eye y", &GMoveCamera::work_space.y);
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::InputFloat("##eye z", &GMoveCamera::work_space.z);
    ImGui::NewLine();

    ImGui::Text("Looks origin (Position + Direction):");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::InputFloat("##center x", &GMoveCamera::view_center.x);
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::InputFloat("##center y", &GMoveCamera::view_center.y);
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::InputFloat("##center z", &GMoveCamera::view_center.z);
    ImGui::NewLine();

    ImGui::Text("Up (Up):");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::InputFloat("##up x", &GMoveCamera::view_up.x);
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::InputFloat("##up y", &GMoveCamera::view_up.y);
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::InputFloat("##up z", &GMoveCamera::view_up.z);
    ImGui::NewLine();
    /* END VIEW */

    ImGui::End();
}