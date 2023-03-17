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
    int height = 480;
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
    glfwSwapInterval(1);
    glewExperimental = true;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error to init GLEW" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetKeyCallback(window, key_callback);

    while (glfwWindowShouldClose(window) == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        /* IMGUI */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (GMoveCamera::pause)
            imGuiMenuBar();

        ImGui::Render();
        /* END IMGUI */

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

        /* glm::mat4 projection;
        if (GMoveCamera::projection_type_index == 0)
            projection = glm::perspective(glm::radians(GMoveCamera::projection_field_of_view),
                                          GMoveCamera::PROJECTION_RATIOS_VALUES[GMoveCamera::projection_ratio_index],
                                          GMoveCamera::projection_unit_init, GMoveCamera::projection_unit_end);
        else if (GMoveCamera::projection_type_index == 1)
            projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

        glm::mat4 view = glm::lookAt(
            GMoveCamera::view_eye,
            GMoveCamera::view_center,
            GMoveCamera::view_up);

        glm::mat4 model(1.0f); */

        if (!GMoveCamera::pause)
            computeMatricesFromInputs(window, width, height);
        mat4 projection = getProjectionMatrix();
        mat4 view = getViewMatrix();
        glm::mat4 mvp = projection * view * mat4(1.0f);
        mat4 model(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, cubeVertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        /* IMGUI RENDER */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* END IMGUI RENDER */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}