#include "./LoadModel.h"

using namespace glm;

bool loadModel_pause = false;
bool loadModel_inverted_mouse = false;

void loadModelKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        loadModel_pause = !loadModel_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        loadModel_inverted_mouse = !loadModel_inverted_mouse;
}

void loadModel()
{
    Engine engine{};
    Camera camera{engine.getWidth(), engine.getHeight()};

    engine.init("Load model");
    Texture::Init();

    engine.setKeyCallback(loadModelKeyCallback);

    Shader shader{"./shaders/loadModel/loadModel.vert", "./shaders/loadModel/loadModel.frag"};

    Model ourModel{"./assets/models/backpack.obj"};

    while (engine.isClose())
    {
        engine.newFrame();

        mat4 projection = perspective(radians(45.0f), (float)engine.getWidth() / (float)engine.getHeight(),
                                      1.0f, 100.0f);
        mat4 view;
        if (!loadModel_pause)
            view = camera.getViewMatrix(engine.getWindow(),
                                        engine.getWidth(), engine.getHeight(),
                                        loadModel_inverted_mouse);

        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        mat4 model;
        model = translate(model, vec3{0.0f});
        model = scale(model, vec3{1.0f});
        shader.setMat4("model", model);
        ourModel.draw(shader);

        engine.renderFrame();
    }

    engine.terminate();
}