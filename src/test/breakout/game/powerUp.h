#pragma once

#include <string>

#include "../../../engine/Engine.h"

#include "gameObject.h"

const glm::vec2 POWERUP_SIZE{60.0f, 20.0f};
const glm::vec2 POWERUP_VELOCITY{0.0f, 150.0f};

class PowerUp : public GameObject
{
public:
  std::string type;
  float duration;
  bool activated;

  PowerUp(std::string type, glm::vec3 color, float duration,
          glm::vec2 position, Texture texture)
      : GameObject{position, POWERUP_SIZE, texture, color, POWERUP_VELOCITY},
        type{type}, duration{duration}, activated() {}
};