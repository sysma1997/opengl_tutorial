#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../../../engine/Engine.h"
#include "../../../engine/resourceManager/ResourceManager.h"
#include "../../../engine/2D/Sprite2D.h"

#include "gameObject.h"
#include "gameLevel.h"
#include "ballObject.h"

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

    std::vector<GameLevel> levels;
    unsigned int level;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();

    // loop
    void processInput(float dt);
    void update(float dt);
    void render();
};