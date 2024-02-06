#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Shader/Shader.h>
#include <Texture/Texture.h>

#include "GameObject.h"

struct Particle2D
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    float life;

    Particle2D() : position{ 0.0f }, velocity{ 0.0f }, color{ 1.0f }, life{ 0.0f } {}
};

class Particle2DGenerator
{
private:
    Shader shader;
    Texture texture;
    unsigned int amount;

    std::vector<Particle2D> particles;
    unsigned int VAO;

    void init();
    unsigned int lastUsed;
    unsigned int firstUnused();
    void respawn(Particle2D& particle, GameObject& object, glm::vec2 offset = glm::vec2{ 0.0f });

public:
    Particle2DGenerator(Shader shader, Texture texture, unsigned int amount);
    void update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2{ 0.0f });
    void draw();
};