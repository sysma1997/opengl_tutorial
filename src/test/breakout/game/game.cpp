#include "./game.h"

Sprite2D *renderer;

const glm::vec2 PLAYER_SIZE{100.0f, 20.0f};
const float PLAYER_VELOCITY{500.0f};

GameObject *player;

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), keys(),
                                                      width(width), height(height) {}
Game::~Game()
{
    delete renderer;
}

void Game::init()
{
    ResourceManager::LoadShader("./shaders/game/game.vert", "./shaders/game/game.frag", "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use();
    ResourceManager::GetShader("sprite").setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);

    Shader shader = ResourceManager::GetShader("sprite");
    renderer = new Sprite2D(shader);

    ResourceManager::LoadTexture("./assets/textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("./assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("./assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("./assets/textures/block_solid.png", false, "block_solid");

    for (int i = 0; i < 4; i++)
    {
        GameLevel gameLevel;
        std::string path = "./assets/game/level/" + std::to_string(i + 1) + ".lvl";
        gameLevel.load(path.c_str(), width, height / 2);
        levels.push_back(gameLevel);
    }
    level = 0;

    ResourceManager::LoadTexture("./assets/textures/paddle.png", true, "paddle");
    glm::vec2 pos{(static_cast<float>(width) / 2.0f) - PLAYER_SIZE.x / 2.0f,
                  static_cast<float>(height) - PLAYER_SIZE.y};
    player = new GameObject{pos, PLAYER_SIZE, ResourceManager::GetTexture("paddle")};
}
void Game::processInput(float dt)
{
    if (state == GameState::ACTIVE)
    {
        float velocity{PLAYER_VELOCITY * dt};

        if (keys[GLFW_KEY_LEFT] && player->position.x >= 0.0f)
            player->position.x -= velocity;
        if (keys[GLFW_KEY_RIGHT] && player->position.x <= width - PLAYER_SIZE.x)
            player->position.x += velocity;
    }
}
void Game::update(float dt) {}
void Game::render()
{
    if (state == GameState::ACTIVE)
    {
        player->draw(*renderer);
        levels[level].draw(*renderer);

        renderer->draw(ResourceManager::GetTexture("background"),
                       glm::vec2{0.0f}, glm::vec2{width, height}, 0.0f);
    }
}