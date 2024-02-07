#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <irrKlang/irrKlang.h>

#include <Engine.h>

#include "GameObject.h"
#include "GameLevel.h"
#include "GameBallObject.h"
#include "GameParticle2D.h"
#include "GamePostProcessing.h"
#include "PowerUp.h"

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

    std::vector<PowerUp> powerUps;

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

    void spawnPowerUp(GameObject& block);
    void updatePowerUp(float dt);

    void terminate();
};
