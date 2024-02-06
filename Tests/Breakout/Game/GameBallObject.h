#pragma once

#include <glm/glm.hpp>

#include <Engine.h>

#include "GameObject.h"

class BallObject : public GameObject
{
public:
    float radius;
    bool stuck;
    bool sticky, passThrough;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture texture);

    glm::vec2 move(float dt, unsigned int window_width);
    void reset(glm::vec2 position, glm::vec2 velocity);
};