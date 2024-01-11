#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <glm/glm.hpp>

#include "../../../engine/Engine.h"

#include "gameObject.h"
#include "gameLevel.h"
#include "ballObject.h"
#include "gamePostProcessing.h"

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
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

    void doCollisions();

    void resetLevel();
    void resetPlayer();
};