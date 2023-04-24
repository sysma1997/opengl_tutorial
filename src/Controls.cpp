#include "Controls.h"

using namespace glm;

mat4 viewMatrix;
mat4 projectionMatrix;

mat4 getViewMatrix()
{
    return viewMatrix;
}
mat4 getProjectionMatrix()
{
    return projectionMatrix;
}

vec3 position = vec3(0.0f, 0.0f, 5.0f);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;

vec3 direction(0.0f);
vec3 right(1.0f);
vec3 up(0.0f, 1.0f, 0.0f);

float speed = 3.0f;
float mouseSpeed = 0.005f;

void computeMatricesFromInputs(GLFWwindow *window, int width, int height)
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xpos = width / 2;
    double ypos = height / 2;

    float _speed = speed;
    if (!GMoveCamera::pause)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetCursorPos(window, width / 2, height / 2);

        horizontalAngle += mouseSpeed * float(width / 2 - xpos);
        verticalAngle += mouseSpeed * float(height / 2 - ypos);

        direction = vec3(0.0f);
        right = vec3(1.0f);
        up = vec3(1.0f);
        direction = vec3(cos(verticalAngle) * sin(horizontalAngle),
                         sin(verticalAngle),
                         cos(verticalAngle) * cos(horizontalAngle));
        right = vec3(sin(horizontalAngle - 3.14f / 2.0f),
                     0,
                     cos(horizontalAngle - 3.14f / 2.0f));
        up = cross(right, direction);

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            _speed *= 2;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += direction * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= direction * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += right * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= right * deltaTime * _speed;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            position -= up * deltaTime * _speed;

        GMoveCamera::work_space = position;
        GMoveCamera::view_center = position + direction;
        GMoveCamera::view_up = up;
    }

    if (GMoveCamera::projection_type_index == 0)
    {
        projectionMatrix = perspective(
            radians(GMoveCamera::projection_field_of_view),
            GMoveCamera::PROJECTION_RATIOS_VALUES[GMoveCamera::projection_ratio_index],
            GMoveCamera::projection_unit_init, GMoveCamera::projection_unit_end);
    }
    else
    {
        projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
    }
    viewMatrix = lookAt(GMoveCamera::work_space,
                        GMoveCamera::view_center,
                        GMoveCamera::view_up);

    lastTime = currentTime;
}