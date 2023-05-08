#include "./Rectangle.h"

#include "../../../libs/stb_image.h"

void rectangle()
{
    Engine engine = Engine();
    engine.init("Rectangle");
    Texture::Init();

    Shader shader("./shaders/rectangle/rectangle.vert", "./shaders/rectangle/rectangle.frag");

    float vertices[] = {
        // position(3), texture(2)
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // right top and top
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // right bottom and bottom
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // left top and top
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // left bottom and bottom
    };
    unsigned int indices[] = {
        0, 1, 2, // first triangle
        2, 1, 3, // seconds triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Texture texture1{"./assets/textures/container.jpg"};
    Texture texture2{"./assets/textures/awesomeface.png", true};

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (engine.isClose())
    {
        engine.newFrame();

        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.getId());

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        engine.renderFrame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.id);

    engine.terminate();
}