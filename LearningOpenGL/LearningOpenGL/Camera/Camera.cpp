#include "Camera.h"

using namespace glm;

Camera::Camera(int width, int height)
{
    position = vec3(0.0f, 0.0f, 3.0f);
    front = vec3(0.0f, 0.0f, 0.0f);
    up = vec3(0.0f, 1.0f, 0.0f);

    horizontalAngle = 0.0f;
    verticalAngle = 0.0f;

    yaw = -90.0f;
    pitch = 0.0f;
    mouseLastX = width / 2.0f;
    mouseLastY = height / 2.0f;
    mouseSpeed = 0.1f;

    speed = 2.0f;
}
Camera::~Camera() {}

vec3 Camera::getPosition()
{
    return position;
}
vec3 Camera::getFront()
{
    return front;
}
mat4 Camera::getViewMatrix(GLFWwindow* window, int width, int height, bool inverted)
{
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    double xpos = width / 2;
    double ypos = height / 2;

    float _speed = speed;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle = xpos - (width / 2);
    verticalAngle = (height / 2) - ypos;
    if (inverted)
        verticalAngle = ypos - (height / 2);

    horizontalAngle *= mouseSpeed;
    verticalAngle *= mouseSpeed;

    yaw += horizontalAngle;
    pitch += verticalAngle;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 _front;
    _front.x = cos(radians(yaw)) * cos(radians(pitch));
    _front.y = sin(radians(pitch));
    _front.z = sin(radians(yaw)) * cos(radians(pitch));
    front = normalize(_front);

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

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        position += up * deltaTime * _speed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        position -= up * deltaTime * _speed;

    mat4 viewMatrix = lookAt(position, position + front, up);

    return viewMatrix;
}
