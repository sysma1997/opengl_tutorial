#include "LoadModels.h"

using namespace glm;

bool loadModel_pause = false;
bool loadModel_inverted_mouse = false;

void loadModelKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        loadModel_pause = !loadModel_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        loadModel_inverted_mouse = !loadModel_inverted_mouse;
}

void loadModels()
{
    Engine* engine{ new Engine{} };
    Camera* camera{ new Camera{engine->width, engine->height} };

    engine->init("Load model");
    Texture::Init();

    engine->setKeyCallback(loadModelKeyCallback);

    Shader* shader{ new Shader{ "Shaders/loadModel/loadModel.vert", "Shaders/loadModel/loadModel.frag" } };
    Model* ourModel{ new Model{ "Assets/models/backpack/backpack.obj" } };

    glClearColor(0.3f, 0.6f, 0.8f, 1.0f);
    mat4 view{};
    while (engine->isClose())
    {
        engine->newFrame();

        mat4 projection = perspective(radians(45.0f), engine->fWidth() / engine->fHeight(),
            1.0f, 100.0f);
        if (!loadModel_pause)
            view = camera->getViewMatrix(engine->window, engine->width, engine->height, loadModel_inverted_mouse);
        mat4 model = mat4(1.0f);
        model = translate(model, vec3{ 0.0f, 0.0f, 0.0f });
        model = scale(model, vec3{ 1.0f, 1.0f, 1.0f });

        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);
        ourModel->draw(*shader);

        engine->renderFrame();
    }

    engine->terminate();
}