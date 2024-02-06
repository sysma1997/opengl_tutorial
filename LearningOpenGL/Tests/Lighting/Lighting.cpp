#include "Lighting.h"

using namespace glm;

bool lighting_pause = false;
bool lighting_inverted_mouse = false;

void colorKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        lighting_pause = !lighting_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        lighting_inverted_mouse = !lighting_inverted_mouse;
}

void lighting()
{
    Engine* engine{ new Engine{} };
    UI* ui{ new UI{} };
    Camera* camera{ new Camera{ engine->width, engine->height } };

    engine->init("Colors");
    Texture::Init();

    engine->setKeyCallback(colorKeyCallback);
    ui->init(engine->window);

    Shader* cubeShader{ new Shader{"./shaders/lighting/lighting.vert", "./shaders/lighting/lightingCube.frag"} };
    Shader* lightShader{ new Shader{"./shaders/lighting/lighting.vert", "./shaders/lighting/lightingConst.frag"} };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
    vec3 cubePositions[] = {
        vec3(0.0f, 0.0f, 0.0f),
        vec3(2.0f, 5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3(2.4f, -0.4f, -3.5f),
        vec3(-1.7f, 3.0f, -7.5f),
        vec3(1.3f, -2.0f, -2.5f),
        vec3(1.5f, 2.0f, -2.5f),
        vec3(1.5f, 0.2f, -1.5f),
        vec3(-1.3f, 1.0f, -1.5f) };
    vec3 pointLightPositions[] = {
        vec3(0.7f, 0.2f, 2.0f),
        vec3(2.3f, -3.3f, -4.0f),
        vec3(-4.0f, 2.0f, -12.0f),
        vec3(0.0f, 0.0f, -3.0f) };

    GLuint cubeVAO, VBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Texture diffuseMap{ "./assets/textures/container2.png", true };
    Texture specularMap{ "./assets/textures/container2_specular.png", true };

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vec3 lightPos(1.2f, 1.0f, 2.0f);

    float cube_modal[3] = { 0.0f, 0.0f, 0.0f };

    cubeShader->use();
    cubeShader->setInt("material.diffuse", 0);
    cubeShader->setInt("material.specular", 1);

    mat4 view{};
    while (engine->isClose())
    {
        engine->newFrame();

        mat4 projection = perspective(radians(45.0f), engine->fWidth() / engine->fHeight(), 0.1f, 100.0f);
        
        if (!lighting_pause)
            view = camera->getViewMatrix(engine->window, engine->width, engine->height, lighting_inverted_mouse);

        // Render cube
        cubeShader->use();
        cubeShader->setMat4("projection", projection);
        cubeShader->setMat4("view", view);
        cubeShader->setVec3("viewPos", camera->getPosition());

        cubeShader->setFloat("material.shininess", 64.0f);

        // directional light
        cubeShader->setVec3("dirLight.direction", vec3(-0.2f, -1.0f, -0.3f));
        cubeShader->setVec3("dirLight.ambient", vec3(0.05f, 0.05f, 0.05f));
        cubeShader->setVec3("dirLight.diffuse", vec3(0.4f, 0.4f, 0.4f));
        cubeShader->setVec3("dirLight.specular", vec3(0.5f, 0.5f, 0.5f));
        // point light 1
        cubeShader->setVec3("pointLights[0].position", pointLightPositions[0]);
        cubeShader->setVec3("pointLights[0].ambient", vec3(0.05f, 0.05f, 0.05f));
        cubeShader->setVec3("pointLights[0].diffuse", vec3(0.8f, 0.8f, 0.8f));
        cubeShader->setVec3("pointLights[0].specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setFloat("pointLights[0].constant", 1.0f);
        cubeShader->setFloat("pointLights[0].linear", 0.09f);
        cubeShader->setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        cubeShader->setVec3("pointLights[1].position", pointLightPositions[1]);
        cubeShader->setVec3("pointLights[1].ambient", vec3(0.05f, 0.05f, 0.05f));
        cubeShader->setVec3("pointLights[1].diffuse", vec3(0.8f, 0.8f, 0.8f));
        cubeShader->setVec3("pointLights[1].specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setFloat("pointLights[1].constant", 1.0f);
        cubeShader->setFloat("pointLights[1].linear", 0.09f);
        cubeShader->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        cubeShader->setVec3("pointLights[2].position", pointLightPositions[2]);
        cubeShader->setVec3("pointLights[2].ambient", vec3(0.05f, 0.05f, 0.05f));
        cubeShader->setVec3("pointLights[2].diffuse", vec3(0.8f, 0.8f, 0.8f));
        cubeShader->setVec3("pointLights[2].specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setFloat("pointLights[2].constant", 1.0f);
        cubeShader->setFloat("pointLights[2].linear", 0.09f);
        cubeShader->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        cubeShader->setVec3("pointLights[3].position", pointLightPositions[3]);
        cubeShader->setVec3("pointLights[3].ambient", vec3(0.05f, 0.05f, 0.05f));
        cubeShader->setVec3("pointLights[3].diffuse", vec3(0.8f, 0.8f, 0.8f));
        cubeShader->setVec3("pointLights[3].specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setFloat("pointLights[3].constant", 1.0f);
        cubeShader->setFloat("pointLights[3].linear", 0.09f);
        cubeShader->setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        cubeShader->setVec3("spotLight.position", camera->getPosition());
        cubeShader->setVec3("spotLight.direction", camera->getFront());
        cubeShader->setVec3("spotLight.ambient", vec3(0.0f, 0.0f, 0.0f));
        cubeShader->setVec3("spotLight.diffuse", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setVec3("spotLight.specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader->setFloat("spotLight.constant", 1.0f);
        cubeShader->setFloat("spotLight.linear", 0.09f);
        cubeShader->setFloat("spotLight.quadratic", 0.032f);
        cubeShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        cubeShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        /* cubeShader.setVec3("light.position", camera.getPosition());
        cubeShader.setVec3("light.direction", camera.getFront());
        cubeShader.setFloat("light.cutOff", cos(radians(12.5f)));
        cubeShader.setFloat("light.outerCutOff", cos(radians(17.5f))); */

        /* cubeShader.setVec3("light.ambient", vec3(0.2f, 0.2f, 0.2f));
        cubeShader.setVec3("light.diffuse", vec3(0.5f, 0.5f, 0.5f));
        cubeShader.setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));
        cubeShader.setFloat("light.constant", 1.0f);
        cubeShader.setFloat("light.linear", 0.09f);
        cubeShader.setFloat("light.quadratic", 0.032f); */

        mat4 model{1.0f};
        cubeShader->setMat4("model", model);
        /* model = mat4{1.0f};
        model = translate(model, vec3(cube_modal[0], cube_modal[1], cube_modal[2]));
        cubeShader.setMat4("model", model); */

        glActiveTexture(GL_TEXTURE0);
        diffuseMap.bind();
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        /* glBindVertexArray(cubeVAO); */
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Render light
        lightShader->use();
        lightShader->setMat4("projection", projection);
        lightShader->setMat4("view", view);

        /* model = mat4{1.0f};
        model = translate(model, lightPos);
        model = scale(model, vec3(0.2));
        lightShader.setMat4("model", model); */

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = mat4{ 1.0f };
            model = translate(model, pointLightPositions[i]);
            model = scale(model, vec3(0.2f));
            lightShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* ui.newFrame();

        ImGui::SetNextWindowSize(ImVec2(300.0f, 80.0f));
        ImGui::Begin("Cube pos");
        ImGui::Text("Position: (X | Y | Z)");
        ImGui::InputFloat3("##cube_pos", cube_modal);
        ImGui::End();

        ui.renderFrame(); */
        engine->renderFrame();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(cubeShader->id);
    glDeleteProgram(lightShader->id);

    ui->terminate();
    engine->terminate();
}