#pragma once

#include <glm/glm.hpp>

#include "../../../engine/Engine.h"

#include "gameObject.h"

class BallObject : public GameObject
{
public:
    float radius;
    bool stuck;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture texture);

    glm::vec2 move(float dt, unsigned int window_width);
    void reset(glm::vec2 position, glm::vec2 velocity);
};