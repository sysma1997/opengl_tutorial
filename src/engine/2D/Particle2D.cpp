#include "Particle2D.h"

Particle2DGenerator::Particle2DGenerator(Shader shader, Texture texture, unsigned int amount)
    : shader{shader}, texture{texture}, amount{amount}
{
    init();
}

void Particle2DGenerator::init()
{
    unsigned int VBO;
    float quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);

    lastUsed = 0;
    for (unsigned int i{0}; i < amount; i++)
        particles.push_back(Particle2D{});
}

unsigned int Particle2DGenerator::firstUnused()
{
    for (unsigned int i{lastUsed}; i < amount; i++)
    {
        if (particles[i].life <= 0.0f)
        {
            lastUsed = i;
            return i;
        }
    }
    for (unsigned int i{0}; i < lastUsed; i++)
    {
        if (particles[i].life <= 0.0f)
        {
            lastUsed = i;
            return i;
        }
    }

    lastUsed = 0;
    return 0;
}
void Particle2DGenerator::respawn(Particle2D &particle, GameObject &object, glm::vec2 offset)
{
    float random{((rand() % 100) - 50) / 10.0f};
    float color{0.5f + ((rand() % 100) / 100.0f)};
    particle.position = object.position + random + offset;
    particle.color = glm::vec4{color, color, color, 1.0f};
    particle.life = 1.0f;
    particle.velocity = object.velocity * 0.1f;
}

void Particle2DGenerator::update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset)
{
    for (unsigned int i{0}; i < newParticles; i++)
    {
        unsigned int unused{firstUnused()};
        respawn(particles[unused], object, offset);
    }
    for (unsigned int i{0}; i < amount; i++)
    {
        Particle2D &particle{particles[i]};
        particle.life -= dt;
        if (particle.life > 0.0f)
        {
            particle.position -= particle.velocity * dt;
            particle.color.a -= dt * 2.5f;
        }
    }
}
void Particle2DGenerator::draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.use();
    for (Particle2D particle : particles)
    {
        if (particle.life > 0.0f)
        {
            shader.setVec2("offset", particle.position);
            shader.setVec4("color", particle.color);
            texture.bind();

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}