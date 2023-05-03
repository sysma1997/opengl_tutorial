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

vec3 position(0.0f, 0.0f, 3.0f);
vec3 front(0.0f, 0.0f, -1.0f);
vec3 up(0.0f, 1.0f, 0.0f);

float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;

float speed = 3.0f;

float mouseLastX = 0.0f;
float mouseLastY = 0.0f;
float mouseSpeed = 0.1f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void computeMatricesFromInputs(GLFWwindow *window, int width, int height)
{
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    double xpos = width / 2;
    double ypos = height / 2;

    float _speed = speed;
    if (!GMoveCamera::pause)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetCursorPos(window, width / 2, height / 2);

        horizontalAngle += mouseSpeed * float(width / 2 - xpos);
        verticalAngle += mouseSpeed * float(height / 2 - ypos);

        vec3 mouseDirection;
        mouseDirection.x = sin(radians(horizontalAngle)) * cos(radians(verticalAngle));
        mouseDirection.y = sin(radians(verticalAngle));
        mouseDirection.z = cos(radians(horizontalAngle)) * cos(radians(verticalAngle));
        front = normalize(mouseDirection);

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            _speed *= 2;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += front * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= front * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += normalize(cross(front, up)) * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= normalize(cross(front, up)) * deltaTime * _speed;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * deltaTime * _speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            position -= up * deltaTime * _speed;

        GMoveCamera::camera_pos = position;
        GMoveCamera::camera_front = front;
        GMoveCamera::camera_up = up;
    }

    if (GMoveCamera::projection_type_index == 0)
        projectionMatrix = perspective(
            radians(GMoveCamera::projection_field_of_view),
            GMoveCamera::PROJECTION_RATIOS_VALUES[GMoveCamera::projection_ratio_index],
            GMoveCamera::projection_unit_init, GMoveCamera::projection_unit_end);
    else
        projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

    viewMatrix = lookAt(GMoveCamera::camera_pos,
                        GMoveCamera::camera_pos + GMoveCamera::camera_front,
                        GMoveCamera::camera_up);
}