#include "./game.h"

SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), keys(),
                                                      width(width), height(height) {}
Game::~Game()
{
    delete renderer;
}

void Game::init()
{
    ResourceManager::LoadShader("./shaders/game/game.vert", "./shaders/game/game.frag", nullptr, "sprite");
    glm::mat4 projection{glm::ortho(0.0f, static_cast<float>(this->width),
                                    static_cast<float>(this->height), 0.0f, -1.0f, 1.0f)};
    ResourceManager::GetShader("sprite").use().setInteger("image", 0);
    ResourceManager::GetShader("sprite").setMatrix4("projection", projection);

    GameShader shader{ResourceManager::GetShader("sprite")};
    renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("./assets/textures/awesomeface.png", true, "face");
}
void Game::processInput(float dt) {}
void Game::update(float dt) {}
void Game::render()
{
    GameTexture2D texture{ResourceManager::GetTexture("face")};
    renderer->drawSprite(texture,
                         glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                         45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}