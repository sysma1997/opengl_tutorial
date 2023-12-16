#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "../../../engine/Engine.h"
#include "./gameObject.h"

class GameLevel
{
private:
    void init(std::vector<std::vector<unsigned int>> tileData,
              unsigned int levelWidth, unsigned int levelHeight);

public:
    std::vector<GameObject> bricks;

    GameLevel() {}

    void load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    void draw(Sprite2D sprite);
    bool isCompleted();
};