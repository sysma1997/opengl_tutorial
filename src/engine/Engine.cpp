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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error to init GLEW." << std::endl;

        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    /* ImGuiIO &io = ImGui::GetIO();
    (void)io; */

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Engine::renderFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Engine::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}