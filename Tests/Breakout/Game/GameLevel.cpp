#include "GameLevel.h"

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData,
    unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height{ static_cast<unsigned int>(tileData.size()) };
    unsigned int width{ static_cast<unsigned int>(tileData[0].size()) };
    float unit_width{ levelWidth / static_cast<float>(width) };
    float unit_height{ levelHeight / static_cast<float>(height) };

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (tileData[y][x] == 1) // SOLID
            {
                glm::vec2 pos{ unit_width * x, unit_height * y };
                glm::vec2 size{ unit_width, unit_height };
                GameObject brick{ pos, size,
                                 ResourceManager::GetTexture("block_solid"),
                                 glm::vec3{0.8f, 0.8f, 0.7f} };
                brick.isSolid = true;

                bricks.push_back(brick);
            }
            else if (tileData[y][x] > 1) // NO SOLID
            {
                glm::vec2 pos{ unit_width * x, unit_height * y };
                glm::vec2 size{ unit_width, unit_height };
                glm::vec3 color{ 1.0f };
                if (tileData[y][x] == 2)
                    color = glm::vec3{ 0.2f, 0.6f, 1.0f };
                else if (tileData[y][x] == 3)
                    color = glm::vec3{ 0.0f, 0.7f, 0.0f };
                else if (tileData[y][x] == 4)
                    color = glm::vec3{ 0.8f, 0.8f, 0.4f };
                else if (tileData[y][x] == 5)
                    color = glm::vec3{ 1.0f, 0.5f, 0.0f };

                bricks.push_back(GameObject{ pos, size,
                                            ResourceManager::GetTexture("block"), color });
            }
        }
    }
}

void GameLevel::load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    bricks.clear();

    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream{ file };
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream{ line };
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);

            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            init(tileData, levelWidth, levelHeight);
    }
}
void GameLevel::draw(Sprite2D& sprite)
{
    for (GameObject& tile : bricks)
        if (!tile.destroyed)
            tile.draw(sprite);
}
bool GameLevel::isCompleted()
{
    for (GameObject& tile : bricks)
        if (!tile.isSolid && !tile.destroyed)
            return false;

    return true;
}