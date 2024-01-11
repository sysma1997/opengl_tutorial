#include "./Sprite2D.h"

Sprite2D::Sprite2D(Shader &shader)
{
    this->shader = shader;
    initData();
}
Sprite2D::~Sprite2D()
{
    glDeleteVertexArrays(1, &quadVAO);
}

void Sprite2D::initData()
{
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite2D::draw(Texture texture,
                    glm::vec2 position,
                    glm::vec2 size,
                    float rotate,
                    glm::vec3 color)
{
    shader.use();
    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.setMat4("model", model);
    shader.setVec3("spriteColor", color);
    texture.bind();

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}