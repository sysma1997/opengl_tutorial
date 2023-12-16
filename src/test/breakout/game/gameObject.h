#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../../../engine/texture/Texture.h"
#include "../../../engine/2D/Sprite2D.h"

class GameObject
{
public:
    glm::vec2 position, size, velocity;
    glm::vec3 color;
    float rotation;
    bool isSolid;
    bool destroyed;

    Texture texture;

    GameObject();
    GameObject(glm::vec2 position, glm::vec2 size, Texture texture,
               glm::vec3 color = glm::vec3{1.0f},
               glm::vec2 velocity = glm::vec2{0.0f});

    virtual void draw(Sprite2D &sprite);
};