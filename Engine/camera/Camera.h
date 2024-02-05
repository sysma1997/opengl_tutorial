#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::mat4 viewMatrix;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float horizontalAngle;
    float verticalAngle;

    float yaw;
    float pitch;
    float mouseLastX;
    float mouseLastY;
    float mouseSpeed;

    float deltaTime;
    float lastFrame;
    float speed;

public:
    Camera(int width, int height);
    ~Camera();

    glm::vec3 getPosition();
    glm::vec3 getFront();

    glm::mat4 getViewMatrix(GLFWwindow* window, int width, int height, bool inverted = false);
};