#include "Controls.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;

void computeMatricesFromInputs(GLFWwindow *window, int width, int height)
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle += mouseSpeed * float(width / 2 - xpos);
    verticalAngle += mouseSpeed * float(height / 2 - ypos);

    vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                   sin(verticalAngle),
                   cos(verticalAngle) * cos(horizontalAngle));
    vec3 right(sin(horizontalAngle - 3.14f / 2.0f),
               0,
               cos(horizontalAngle - 3.14f / 2.0f));
    vec3 up = cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += direction * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= direction * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * deltaTime * speed;

    float FoV = initialFoV;

    projectionMatrix = perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = lookAt(position,
                        position + direction,
                        up);

    lastTime = currentTime;
}