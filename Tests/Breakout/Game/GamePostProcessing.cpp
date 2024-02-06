#include "GamePostProcessing.h"

GamePostProcessing::GamePostProcessing(Shader shader, unsigned int width, unsigned int height)
    : shader{ shader }, texture{}, width{ width }, height{ height }, chaos{ false }, confuse{ false }, shake{ false }
{
    glGenFramebuffers(1, &MSFBO);
    glGenFramebuffers(1, &FBO);
    glGenRenderbuffers(1, &RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SYSMA::BREAKOUT::GamePostProcessing: Error post processing failed to initialize MSFBO.\n";

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    texture.generate(width, height, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SYSMA::BREAKOUT::GamePostProcessing: Error post processing failed to initialize FBO.\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    initRenderData();
    shader.use();
    shader.setInt("Scene", 0);
    float offset = 1.0f / 300.0f;
    float offsets[9][2]{
        {-offset, offset},
        {0.0f, offset},
        {offset, offset},
        {-offset, 0.0f},
        {0.0f, 0.0f},
        {offset, 0.0f},
        {-offset, -offset},
        {0.0f, -offset},
        {offset, -offset} };
    glUniform2fv(glGetUniformLocation(shader.id, "offsets"), 9, (float*)offsets);
    int edgeKernel[9]{
        -1, -1, -1,
        -1, 8, -1,
        -1, -1, -1 };
    glUniform1iv(glGetUniformLocation(shader.id, "edgeKernel"), 9, edgeKernel);
    float blurKernel[9]{
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
        2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f };
    glUniform1fv(glGetUniformLocation(shader.id, "blurKernel"), 9, blurKernel);
}

void GamePostProcessing::initRenderData()
{
    unsigned int VBO;
    float vertices[]{
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GamePostProcessing::beginReder()
{
    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void GamePostProcessing::endRender()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void GamePostProcessing::render(float time)
{
    shader.use();
    shader.setFloat("time", time);
    shader.setInt("chaos", chaos);
    shader.setInt("confuse", confuse);
    shader.setInt("shake", shake);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}