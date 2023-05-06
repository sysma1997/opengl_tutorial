#include "./Triangle.h"

using namespace glm;

void triangle()
{
    Engine engine{};
    UI ui{};

    engine.init("Triangle");
    ui.init(engine.getWindow());

    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // right down
        -0.5f, -0.5f, 0.0f, // left down
        0.0f, 0.5f, 0.0f,   // up
    };

    Shader shader("./shaders/triangle/triangle.vert", "./shaders/triangle/triangle.frag");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float imGuiMinWinSize[] = {
        250.0f, 80.0f, // ImGui windows min size
    };
    float color[] = {
        1.0f, 1.0f, 1.0f, // RGB
    };

    while (engine.isClose())
    {
        engine.newFrame();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ui.newFrame();

        if (imGuiMinWinSize[0] < 250.0f)
            imGuiMinWinSize[0] = 250.0f;
        if (imGuiMinWinSize[1] < 80.0f)
            imGuiMinWinSize[1] = 80.0f;

        ImGui::SetNextWindowSize(ImVec2(imGuiMinWinSize[0], imGuiMinWinSize[1]));
        ImGui::Begin("Change color triangle", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Color");
        ImGui::ColorEdit3("##color", color);

        ImGui::End();

        shader.use();
        shader.setVec3("color", vec3(color[0], color[1], color[2]));

        ui.renderFrame();
        engine.renderFrame();
    }

    ui.terminate();
    engine.terminate();
}