#include "Breakout.h"

Game* game{ new Game{ SCREEN_WIDTH, SCREEN_HEIGHT } };

void breakoutKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game->keys[key] = true;
        else if (action == GLFW_RELEASE) {
            game->keys[key] = false;
            game->keyProcessed[key] = false;
        }
    }
}

void breakout()
{
    Engine* engine{ new Engine{} };

    engine->init("breakout", true);

    engine->setKeyCallback(breakoutKeyCallback);

    game->init();

    float deltaTime{ 0.0f };
    float lastFrame{ 0.0f };

    while (engine->isClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        engine->newFrame();

        game->processInput(deltaTime);
        game->update(deltaTime);

        game->render();

        engine->renderFrame();
    }

    ResourceManager::Clear();
    game->terminate();
    engine->terminate();
}
