#include "ballObject.h"

BallObject::BallObject()
    : GameObject(), radius{12.5f}, stuck{true}, sticky{false}, passThrough{false} {}
BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture texture)
    : GameObject{pos, glm::vec2{radius * 2.0f}, texture, glm::vec3{1.0f}, velocity},
      radius{radius}, stuck{true}, sticky{false}, passThrough{false} {}

glm::vec2 BallObject::move(float dt, unsigned int window_width)
{
    if (!stuck)
    {
        position += velocity * dt;

        if (position.x <= 0.0f)
        {
            velocity.x = -velocity.x;
            position.x = 0.0f;
        }
        else if (position.x + size.x >= window_width)
        {
            velocity.x = -velocity.x;
            position.x = window_width - size.x;
        }

        if (position.y <= 0.0f)
        {
            velocity.y = -velocity.y;
            position.y = 0.0f;
        }
    }

    return position;
}
void BallObject::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    stuck = true;
    sticky = false;
    passThrough = false;
}