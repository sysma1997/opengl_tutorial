#include "./Engine.h"

Engine::Engine()
{
    width = 800;
    height = 600;
}
Engine::Engine(int width, int height)
{
    this->width = width;
    this->height = height;
}
Engine::~Engine() {}

int Engine::getWidth()
{
    return width;
}
int Engine::getHeight()
{
    return height;
}
GLFWwindow *Engine::getWindow()
{
    return window;
}

void Engine::init(const char *title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW." << std::endl;

        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error to open window with GLFW, if use old GPU, "
                  << "it's not compatible with OpenGL 3.3" << std::endl;

        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = true;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error to init GLEW." << std::endl;

        return;
    }

    glEnable(GL_DEPTH_TEST);

    stbi_set_flip_vertically_on_load(true);
}
bool Engine::isClose()
{
    return glfwWindowShouldClose(window) == 0;
}
void Engine::newFrame()
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Engine::renderFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Engine::terminate()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::setKeyCallback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(window, callback);
}