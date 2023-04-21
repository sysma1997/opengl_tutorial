#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./libs/imgui/imgui.h"
#include "./libs/imgui/imgui_impl_glfw.h"
#include "./libs/imgui/imgui_impl_opengl3.h"

#include "./src/ShaderCompiler.h"
#include "./src/imguiScreens/menuBar.h"
#include "./src/imguiScreens/moveCamera/moveCamera.h"
#include "./src/LoadTextures.h"
#include "./src/Controls.h"
#include "./src/LoadModels.h"

using namespace glm;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        GMoveCamera::pause = !GMoveCamera::pause;
}

int main(void)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW." << std::endl;

        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800;
    int height = 600;
    GLFWwindow *window;
    window = glfwCreateWindow(width, height, "OpenGL Learning", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error to open window with GLFW, if use old GPU, it's not compatible with OpenGL 3.3"
                  << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    /* glfwSwapInterval(1);
    glewExperimental = true; */

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error to init GLEW" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    /* glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE); */

    /* GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = shaderCompiler("./shaders/test.vert", "./shaders/test.frag");

    GLuint texture = LoadTextureDDS("./assets/textures/uvmap_2.DDS");

    GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

    std::vector<glm::vec3> cubeVertices;
    std::vector<glm::vec2> cubeUvs;
    std::vector<glm::vec3> cubeNormals;
    LoadModelObj("./assets/models/suzanne.obj", cubeVertices, cubeUvs, cubeNormals);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(glm::vec3), &cubeVertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeUvs.size() * sizeof(glm::vec2), &cubeUvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeNormals.size() * sizeof(glm::vec3), &cubeNormals[0], GL_STATIC_DRAW); */

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetKeyCallback(window, key_callback);

    GLuint programID = shaderCompiler("./shaders/triangle.vert", "./shaders/triangle.frag");

    float triangle_first[] = {
        //
        -0.9f, -0.5f, 0.0f, // left
        -0.45f, 0.5f, 0.0f, // top
        0.0f, -0.5f, 0.0f,  // right
    };
    float triangle_second[] = {
        //
        0.0f, -0.5f, 0.0f, // left
        0.9f, -0.5f, 0.0f, // right
        0.45f, 0.5f, 0.0f, // top
    };
    /* unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2, // first triangle
        3, 4, 2  // second triangle
    }; */

    GLuint VBO[2], VAO[2] /* , EBO */;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    /* glGenBuffers(1, &EBO); */

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_first), triangle_first, GL_STATIC_DRAW);

    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_second), triangle_second, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (glfwWindowShouldClose(window) == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* IMGUI */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        imGuiMenuBar();

        ImGui::Render();
        /* END IMGUI */

        /* glUseProgram(programID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        computeMatricesFromInputs(window, width, height);
        mat4 projection = getProjectionMatrix();
        mat4 view = getViewMatrix();
        mat4 model(1.0f);
        glm::mat4 mvp = projection * view * model;

        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &model[0][0]);

        glm::vec3 lightPos(4, 4, 4);
        glUniform3f(glGetUniformLocation(programID, "LightPosition_world"),
                    lightPos.x, lightPos.y, lightPos.z);

        glDrawArrays(GL_TRIANGLES, 0, cubeVertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2); */

        glUseProgram(programID);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* IMGUI RENDER */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* END IMGUI RENDER */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    /* glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VertexArrayID); */

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    /* glDeleteBuffers(1, &EBO); */
    glDeleteProgram(programID);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}