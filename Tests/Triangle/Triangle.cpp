#include "Triangle.h"

using namespace glm;

void triangle() {
    Engine* engine{ new Engine{} };
    UI* ui{ new UI{} };

    engine->init("Triangle");
    ui->init(engine->window);

    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // right down
        -0.5f, -0.5f, 0.0f, // left down
        0.0f, 0.5f, 0.0f,   // up
    };

    Shader* shader{ new Shader{"Shaders/triangle/triangle.vert", "Shaders/triangle/triangle.frag"} };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float imGuiMinWinSize[] = {
        250.0f, 80.0f, // ImGui windows min size
    };
    float color[] = {
        1.0f, 1.0f, 1.0f, // RGB
    };

    while (engine->isClose())
    {
        engine->newFrame();

        shader->use();
        shader->setVec3("color", vec3(color[0], color[1], color[2]));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ui->newFrame();

        if (imGuiMinWinSize[0] < 250.0f)
            imGuiMinWinSize[0] = 250.0f;
        if (imGuiMinWinSize[1] < 80.0f)
            imGuiMinWinSize[1] = 80.0f;

        ImGui::SetNextWindowSize(ImVec2(imGuiMinWinSize[0], imGuiMinWinSize[1]));
        ImGui::Begin("Change color triangle", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Color");
        ImGui::ColorEdit3("##color", color);

        ImGui::End();

        ui->renderFrame();
        engine->renderFrame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader->id);

    ui->terminate();
    engine->terminate();
}