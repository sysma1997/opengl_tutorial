#include "./Camera.h"

#include <iostream>

using namespace glm;

Camera::Camera()
{
    position = vec3(0.0f, 0.0f, 3.0f);
    front = vec3(0.0f, 0.0f, 0.0f);
    up = vec3(0.0f, 1.0f, 0.0f);

    horizontalAngle = 0.0f;
    verticalAngle = 0.0f;

    mouseLastX = 0.0f;
    mouseLastY = 0.0f;
    mouseSpeed = 0.1f;

    speed = 2.0f;
}
Camera::~Camera() {}

mat4 Camera::getViewMatrix(GLFWwindow *window, int width, int height, bool inverted)
{
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    double xpos = width / 2;
    double ypos = height / 2;

    float _speed = speed;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle += mouseSpeed * float(width / 2 - xpos);
    verticalAngle += mouseSpeed * float(height / 2 - ypos);

    vec3 mouseDirection;
    if (inverted)
        mouseDirection.x = sinf(radians(horizontalAngle)) * cos(radians(verticalAngle));
    else
        mouseDirection.x = sin(radians(horizontalAngle)) * cos(radians(verticalAngle));
    mouseDirection.y = sin(radians(verticalAngle));
    mouseDirection.z = cos(radians(horizontalAngle)) * cos(radians(verticalAngle));
    front = normalize(mouseDirection);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        _speed *= 2;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * deltaTime * _speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * deltaTime * _speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += normalize(cross(front, up)) * deltaTime * _speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= normalize(cross(front, up)) * deltaTime * _speed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += up * deltaTime * _speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= up * deltaTime * _speed;

    mat4 viewMatrix = lookAt(position, position + front, up);

    return viewMatrix;
}