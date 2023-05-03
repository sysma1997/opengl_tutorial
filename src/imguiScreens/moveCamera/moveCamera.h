#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../../../libs/imgui/imgui.h"
#include "../../../libs/imgui/imgui_impl_glfw.h"
#include "../../../libs/imgui/imgui_impl_opengl3.h"

class GMoveCamera
{
public:
    /* PROJECTION VARIABLES */
    static const char *PROJECTION_TYPES[2];
    static int projection_type_index;

    static float projection_field_of_view;

    static float PROJECTION_RATIO_4_3;
    static float PROJECTION_RATIO_5_4;
    static float PROJECTION_RATIO_16_9;
    static const char *PROJECTION_RATIOS[3];
    static const float PROJECTION_RATIOS_VALUES[3];
    static int projection_ratio_index;

    static float projection_unit_init;
    static float projection_unit_end;
    /* END PROJECTION VARIABLES */

    /* VIEW VARIABLES */
    static glm::vec3 camera_pos;
    static glm::vec3 camera_front;
    static glm::vec3 camera_up;
    /* END VIEW VARIABLES */

    static bool pause;

    static float view_angle_rotate_y;
};

void imGuiScreenMoveCamera(bool *open);