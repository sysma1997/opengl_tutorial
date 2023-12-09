#pragma once

#include <glm/glm.hpp>

#include "./shader.h"
#include "./texture.h"

class SpriteRenderer
{
private:
    GameShader shader;
    unsigned int quadVAO;

    void initRederData();

public:
    SpriteRenderer(GameShader &shader);
    ~SpriteRenderer();

    void drawSprite(GameTexture2D &texture,
                    glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f),
                    float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
};