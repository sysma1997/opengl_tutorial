#include "./breakout.h"

#include <iostream>

Game game{SCREEN_WIDTH, SCREEN_HEIGHT};

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.keys[key] = true;
        else if (action == GLFW_RELEASE)
            game.keys[key] = false;
    }
}

void breakout()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window{glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr)};

    if (!glewInit() != GLEW_OK)
    {
        std::cout << "Error to init GLEW." << '\n';

        return;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.init();

    float deltaTime{0.0f};
    float lastFrame{0.0f};

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        game.processInput(deltaTime);
        game.update(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

    glfwTerminate();
}
