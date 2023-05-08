#include "./Colors.h"

using namespace glm;

bool color_pause = false;
bool color_inverted_mouse = false;

void colorKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        color_pause = !color_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        color_inverted_mouse = !color_inverted_mouse;
}

void colors()
{
    Engine engine{};
    UI ui{};
    Camera camera{};

    engine.init("Colors");

    engine.setKeyCallback(colorKeyCallback);
    ui.init(engine.getWindow());

    Shader shader{"./shaders/lighting/colors/colors.vert", "./shaders/lighting/colors/colors.frag"};
    Shader lightShader{"./shaders/lighting/colors/colors.vert", "./shaders/lighting/colors/colorLight.frag"};

    float CUBE_VERTICES[108] = {
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,

        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,

        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,

        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
    };

    GLuint cubeVAO, VBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vec3 lightPos(1.2f, 1.0f, -2.0f);

    float cube_modal[3] = {0.0f, 0.0f, 0.0f};

    float camera_pos[3] = {0.0f, 0.0f, 0.0f};
    float camera_rotate[2] = {0.0f, 0.0f};

    while (engine.isClose())
    {
        engine.newFrame();

        mat4 projection = perspective(radians(45.0f), (float)engine.getWidth() / (float)engine.getHeight(),
                                      0.1f, 100.0f);

        mat4 view;
        if (!color_pause)
            view = camera.getViewMatrix(engine.getWindow(),
                                        engine.getWidth(), engine.getHeight(),
                                        color_inverted_mouse);

        /* vec3 eye = vec3(camera_pos[0], camera_pos[1], camera_pos[2]);
        vec3 lookat = vec3(0.0f, 0.0f, 0.0f);
        vec3 up = vec3(0.0f, 1.0f, 0.0f);
        view = lookAt(eye, lookat, up); */

        mat4 model;

        // Render cube
        shader.use();
        shader.setVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
        shader.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        model = mat4{1.0f};
        model = translate(model, vec3(cube_modal[0], cube_modal[1], cube_modal[2]));
        shader.setMat4("model", model);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render light
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        model = mat4{1.0f};
        model = translate(model, lightPos);
        model = scale(model, vec3(0.2));
        lightShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ui.newFrame();

        // ImGui::SetNextWindowSize(ImVec2(300.0f, 80.0f));
        ImGui::Begin("Cube pos");
        ImGui::Text("Position: (X | Y | Z)");
        ImGui::InputFloat3("##cube_pos", cube_modal);
        ImGui::End();

        // ImGui::SetNextWindowSize(ImVec2(300.0f, 150.0f));
        ImGui::Begin("Camera");
        ImGui::Text("Position:");
        ImGui::InputFloat3("##camera_pos", camera_pos);
        ImGui::NewLine();
        ImGui::Text("Rotation: (X | Y)");
        ImGui::InputFloat2("##camera_rotate", camera_rotate);
        ImGui::End();

        ui.renderFrame();
        engine.renderFrame();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader.id);
    glDeleteProgram(lightShader.id);

    ui.terminate();
    engine.terminate();
}