#pragma once

#include <glm/glm.hpp>

#include "../../../engine/resourceManager/ResourceManager.h"
#include "../../../engine/2D/Sprite2D.h"

enum GameState
{
    ACTIVE,
    MENU,
    WIN
};

class Game
{
public:
    GameState state;
    bool keys[1024];
    unsigned int width, height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();

    // loop
    void processInput(float dt);
    void update(float dt);
    void render();
};