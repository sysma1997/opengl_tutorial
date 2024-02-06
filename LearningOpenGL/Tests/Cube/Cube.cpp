#include "Cube.h"

using namespace glm;

bool cube_pause = false;
bool cube_inverted_mouse = false;

void cubeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        cube_pause = !cube_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        cube_inverted_mouse = !cube_inverted_mouse;
}

void cube()
{
    Engine* engine{ new Engine{} };
    Camera* camera{ new Camera{engine->width, engine->height} };

    engine->init("Cube");

    engine->setKeyCallback(cubeKeyCallback);

    Shader* shader{ new Shader{"./shaders/cube/cube.vert", "./shaders/cube/cube.frag"} };

    float CUBE_VERTICES[108] = {
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mat4 view{};
    while (engine->isClose())
    {
        engine->newFrame();

        mat4 projection = perspective(radians(45.0f), engine->fWidth() / engine->fHeight(),
            0.1f, 100.0f);
        
        if (!cube_pause)
            view = camera->getViewMatrix(engine->window, engine->width, engine->height, cube_inverted_mouse);
        mat4 model{ 1.0f };

        shader->use();
        shader->setVec3("color", vec3(0.3, 0.7, 0.5));
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        engine->renderFrame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader->id);

    engine->terminate();
}
