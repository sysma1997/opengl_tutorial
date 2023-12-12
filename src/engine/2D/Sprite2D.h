#pragma once

#include <glm/glm.hpp>

#include "../shader/Shader.h"
#include "../texture/Texture.h"

class Sprite2D
{
private:
    Shader shader;
    unsigned int quadVAO;

    void initData();

public:
    Sprite2D(Shader &shader);
    ~Sprite2D();

    void draw(Texture texture,
              glm::vec2 position,
              glm::vec2 size = glm::vec2{10.0f},
              float rotate = 0.0f,
              glm::vec3 color = glm::vec3{1.0f});
};