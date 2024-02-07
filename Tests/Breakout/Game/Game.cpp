#include "Game.h"

using namespace irrklang;

typedef std::tuple<bool, Direction, glm::vec2> Collision;
bool checkCollision(GameObject& one, GameObject& two);
Collision checkCollision(BallObject& one, GameObject& two);
Direction vectorDirection(glm::vec2 target);
bool shouldSpawn(unsigned int change);
void activatePowerUp(PowerUp& powerUp);
bool isOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);

Sprite2D* renderer;
GameObject* player;
const glm::vec2 PLAYER_SIZE{ 100.0f, 20.0f };
const float PLAYER_VELOCITY{ 500.0f };
BallObject* ball;
const glm::vec2 INITIAL_BALL_VELOCITY{ 100.0f, -350.0f };
const float BALL_RADIUS = 12.5f;
Particle2DGenerator* particles;
GamePostProcessing* effects;
float shakeTime = 0.0f;

ISoundEngine* soundEngine{ createIrrKlangDevice() };

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), keys(),
width(width), height(height) {}
Game::~Game()
{
    delete renderer;
    delete player;
    delete ball;
    delete particles;
    delete effects;
    soundEngine->drop();
}

void Game::init()
{
    srand(time(NULL));

    ResourceManager::LoadShader("Shaders/game/game.vert", "Shaders/game/game.frag", "sprite");
    ResourceManager::LoadShader("Shaders/game/particles.vert", "Shaders/game/particles.frag", "particle");
    ResourceManager::LoadShader("Shaders/game/postprocessing.vert", "Shaders/game/postprocessing.frag", "postProcessing");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use();
    ResourceManager::GetShader("sprite").setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);
    ResourceManager::GetShader("particle").use();
    ResourceManager::GetShader("particle").setInt("sprite", 0);
    ResourceManager::GetShader("particle").setMat4("projection", projection);

    ResourceManager::LoadTexture("Assets/textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("Assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("Assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("Assets/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("Assets/textures/particle.png", true, "particle");
    std::string powerUpPath{ "Assets/textures/powerup_" };
    ResourceManager::LoadTexture((powerUpPath + "chaos.png").c_str(), true, "powerup_chaos");
    ResourceManager::LoadTexture((powerUpPath + "confuse.png").c_str(), true, "powerup_confuse");
    ResourceManager::LoadTexture((powerUpPath + "increase.png").c_str(), true, "powerup_increase");
    ResourceManager::LoadTexture((powerUpPath + "passthrough.png").c_str(), true, "powerup_passthrough");
    ResourceManager::LoadTexture((powerUpPath + "speed.png").c_str(), true, "powerup_speed");
    ResourceManager::LoadTexture((powerUpPath + "sticky.png").c_str(), true, "powerup_sticky");

    Shader shader{ ResourceManager::GetShader("sprite") };
    renderer = new Sprite2D{ shader };
    shader = ResourceManager::GetShader("particle");
    Texture texture{ ResourceManager::GetTexture("particle") };
    particles = new Particle2DGenerator{ shader, texture, 500 };
    shader = ResourceManager::GetShader("postProcessing");
    effects = new GamePostProcessing(shader, width, height);

    for (int i = 0; i < 4; i++)
    {
        GameLevel gameLevel;
        std::string path{ "Assets/game/level/" + std::to_string(i + 1) + ".lvl" };
        gameLevel.load(path.c_str(), width, height / 2);
        levels.push_back(gameLevel);
    }
    level = 0;

    ResourceManager::LoadTexture("Assets/textures/paddle.png", true, "paddle");
    glm::vec2 pos{ (static_cast<float>(width) / 2.0f) - PLAYER_SIZE.x / 2.0f,
                  static_cast<float>(height) - PLAYER_SIZE.y };
    player = new GameObject{ pos, PLAYER_SIZE, ResourceManager::GetTexture("paddle") };

    pos = pos + glm::vec2{ PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
                          -BALL_RADIUS * 2.0f };
    ball = new BallObject{ pos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                          ResourceManager::GetTexture("face") };

    resetLevel();
    soundEngine->play2D("Assets/audios/breakout.mp3", true);
}
void Game::processInput(float dt)
{
    if (state == GameState::ACTIVE)
    {
        float velocity{ PLAYER_VELOCITY * dt };

        if (keys[GLFW_KEY_LEFT] && player->position.x >= 0.0f)
        {
            player->position.x -= velocity;
            if (ball->stuck)
                ball->position.x -= velocity;
        }
        if (keys[GLFW_KEY_RIGHT] && player->position.x <= width - PLAYER_SIZE.x)
        {
            player->position.x += velocity;
            if (ball->stuck)
                ball->position.x += velocity;
        }

        if (keys[GLFW_KEY_SPACE])
            ball->stuck = false;
    }
}
void Game::update(float dt)
{
    ball->move(dt, width);
    doCollisions();

    particles->update(dt, *ball, 2, glm::vec2{ ball->radius / 2.0f });

    updatePowerUp(dt);

    if (shakeTime > 0.0f)
    {
        shakeTime -= dt;
        if (shakeTime <= 0.0f)
            effects->shake = false;
    }
    if (ball->position.y >= height)
    {
        resetLevel();
        resetPlayer();
    }
}
void Game::render()
{
    if (state == GameState::ACTIVE)
    {
        effects->beginReder();

        renderer->draw(ResourceManager::GetTexture("background"),
            glm::vec2{ 0.0f }, glm::vec2{ width, height }, 0.0f);

        levels[level].draw(*renderer);
        player->draw(*renderer);

        for (PowerUp& powerUp : powerUps)
            if (!powerUp.destroyed)
                powerUp.draw(*renderer);

        particles->draw();
        ball->draw(*renderer);

        effects->endRender();
        effects->render(static_cast<float>(glfwGetTime()));
    }
}

void Game::doCollisions()
{
    for (GameObject& box : levels[level].bricks)
    {
        if (box.destroyed)
            continue;

        Collision ballCollisionBox{ checkCollision(*ball, box) };
        if (std::get<0>(ballCollisionBox))
        {
            if (!box.isSolid)
            {
                box.destroyed = true;
                spawnPowerUp(box);
                soundEngine->play2D("Assets/audios/bleep.mp3", false);
            }
            else
            {
                shakeTime = 0.05f;
                effects->shake = true;
                soundEngine->play2D("Assets/audios/solid.wav", false);
            }

            Direction direction{ std::get<1>(ballCollisionBox) };
            glm::vec2 diffVec{ std::get<2>(ballCollisionBox) };

            if (!(ball->passThrough && !box.isSolid))
            {
                if (direction == Direction::LEFT || direction == Direction::RIGHT)
                {
                    ball->velocity.x = -ball->velocity.x;
                    float penetration{ ball->radius - std::abs(diffVec.x) };
                    if (direction == Direction::LEFT)
                        ball->position.x += penetration;
                    else
                        ball->position.x -= penetration;
                }
                else
                {
                    ball->velocity.y = -ball->velocity.y;
                    float penetration{ ball->radius - std::abs(diffVec.y) };
                    if (direction == Direction::UP)
                        ball->position.y -= penetration;
                    else
                        ball->position.y += penetration;
                }
            }
        }

        for (PowerUp powerUp : powerUps)
        {
            if (powerUp.destroyed)
                continue;

            if (powerUp.position.y >= height)
                powerUp.destroyed = true;

            if (checkCollision(*player, powerUp))
            {
                activatePowerUp(powerUp);
                powerUp.destroyed = true;
                powerUp.activated = true;
                soundEngine->play2D("Assets/audios/powerup.wav", false);
            }
        }

        Collision ballCollisionPlayer = checkCollision(*ball, *player);
        if (!ball->stuck && std::get<0>(ballCollisionPlayer))
        {
            float centerBoard{ player->position.x + player->size.x / 2.0f };
            float distance{ (ball->position.x + ball->radius) - centerBoard };
            float percentaje{ distance / (player->size.x / 2.0f) };

            float strength{ 2.0f };
            glm::vec2 oldVelocity{ ball->velocity };
            ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentaje * strength;
            ball->velocity.y = std::abs(ball->velocity.y) * -1.0f;
            ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
            ball->stuck = ball->sticky;
            soundEngine->play2D("Assets/audios/bleep.wav", false);
        }
    }
}
void Game::resetLevel()
{
    for (GameObject& box : levels[level].bricks)
    {
        if (!box.isSolid && box.destroyed)
            box.destroyed = false;
    }
}
void Game::resetPlayer()
{
    player->size = PLAYER_SIZE;
    player->position = glm::vec2(static_cast<float>(width) / 2.0f - (PLAYER_SIZE.x / 2.0f),
        static_cast<float>(height) - PLAYER_SIZE.y);
    ball->reset(player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)),
        INITIAL_BALL_VELOCITY);

    effects->chaos = false;
    effects->confuse = false;
    ball->passThrough = false;
    ball->sticky = false;
    player->color = glm::vec3{ 1.0f };
    ball->color = glm::vec3{ 1.0f };
}
void Game::spawnPowerUp(GameObject& block)
{
    if (shouldSpawn(75))
        powerUps.push_back(PowerUp("speed", glm::vec3{ 0.5f, 0.5f, 1.0f }, 0.0f,
            block.position, ResourceManager::GetTexture("powerup_speed")));
    if (shouldSpawn(75))
        powerUps.push_back(PowerUp("sticky", glm::vec3{ 1.0f, 0.5f, 1.0f }, 20.0f,
            block.position, ResourceManager::GetTexture("powerup_sticky")));
    if (shouldSpawn(75))
        powerUps.push_back(PowerUp("pass-through", glm::vec3{ 0.5f, 1.0f, 0.5f }, 10.0f,
            block.position, ResourceManager::GetTexture("powerup_passthrough")));
    if (shouldSpawn(75))
        powerUps.push_back(PowerUp("pad-size-increase", glm::vec3{ 1.0f, 0.6f, 0.4f }, 0.0f,
            block.position, ResourceManager::GetTexture("powerup_increase")));
    if (shouldSpawn(15))
        powerUps.push_back(PowerUp("confuse", glm::vec3{ 1.0f, 0.3f, 0.3f }, 15.0f,
            block.position, ResourceManager::GetTexture("powerup_confuse")));
    if (shouldSpawn(15))
        powerUps.push_back(PowerUp("chaos", glm::vec3{ 0.9f, 0.25f, 0.25f }, 15.0f,
            block.position, ResourceManager::GetTexture("powerup_chaos")));
}
void Game::updatePowerUp(float dt)
{
    for (PowerUp& powerUp : powerUps)
    {
        powerUp.position += powerUp.velocity * dt;
        if (powerUp.activated)
        {
            powerUp.duration -= dt;

            if (powerUp.duration <= 0.0f)
            {
                powerUp.activated = false;

                if (powerUp.type == "sticky")
                {
                    if (!isOtherPowerUpActive(powerUps, "sticky"))
                    {
                        ball->sticky = true;
                        player->color = glm::vec3{ 1.0f };
                    }
                }
                else if (powerUp.type == "pass-through")
                {
                    if (!isOtherPowerUpActive(powerUps, "pass-through"))
                    {
                        ball->passThrough = false;
                        ball->color = glm::vec3{ 1.0f };
                    }
                }
                else if (powerUp.type == "confuse")
                {
                    if (!isOtherPowerUpActive(powerUps, "confuse"))
                    {
                        effects->confuse = false;
                    }
                }
                else if (powerUp.type == "chaos")
                {
                    if (!isOtherPowerUpActive(powerUps, "chaos"))
                    {
                        effects->chaos = false;
                    }
                }
            }
        }
    }

    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(),
        [](const PowerUp& powerUp)
        { return powerUp.destroyed && !powerUp.activated; }),
        powerUps.end());
}

void Game::terminate() {
    soundEngine->stopAllSounds();
}

bool checkCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.position.x + one.size.x >= two.position.x &&
        two.position.x + two.size.x >= one.position.x;
    bool collisionY = one.position.y + one.size.y >= two.position.y &&
        two.position.y + two.size.y >= one.position.y;

    return collisionX && collisionY;
}
Collision checkCollision(BallObject& one, GameObject& two)
{
    glm::vec2 center{ one.position + one.radius };

    glm::vec2 aabbHalfExtends{ two.size.x / 2.0f, two.size.y / 2.0f };
    glm::vec2 aabbCenter{ two.position.x + aabbHalfExtends.x,
                         two.position.y + aabbHalfExtends.y };

    glm::vec2 difference{ center - aabbCenter };
    glm::vec2 clamped{ glm::clamp(difference, -aabbHalfExtends, aabbHalfExtends) };

    glm::vec2 closet{ aabbCenter + clamped };

    difference = closet - center;
    if (glm::length(difference) <= one.radius)
        return std::make_tuple(true, vectorDirection(difference), difference);
    else
        return std::make_tuple(false, Direction::UP, glm::vec2{ 0.0f });
}
Direction vectorDirection(glm::vec2 target)
{
    glm::vec2 compass[]{
        glm::vec2{0.0f, 1.0f},
        glm::vec2{1.0f, 0.0f},
        glm::vec2{0.0f, -1.0f},
        glm::vec2{-1.0f, 0.0f} };
    float max = 0.0f;
    unsigned int bestMatch = -1;

    for (unsigned int i = 0; i < 4; i++)
    {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return static_cast<Direction>(bestMatch);
}
bool shouldSpawn(unsigned int change)
{
    unsigned int random{ rand() % change };
    return random == 0;
}
void activatePowerUp(PowerUp& powerUp)
{
    if (powerUp.type == "speed")
    {
        ball->velocity *= 1.2f;
    }
    else if (powerUp.type == "sticky")
    {
        ball->sticky = true;
        player->color = glm::vec3{ 1.0f, 0.5f, 1.0f };
    }
    else if (powerUp.type == "pass-through")
    {
        ball->passThrough = true;
        ball->color = glm::vec3{ 1.0f, 0.5f, 0.5f };
    }
    else if (powerUp.type == "pad-size-increase")
    {
        player->size.x += 50.0f;
    }
    else if (powerUp.type == "confuse")
    {
        if (!effects->chaos)
            effects->confuse = true;
    }
    else if (powerUp.type == "chaos")
    {
        if (!effects->confuse)
            effects->chaos = true;
    }
}
bool isOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
    for (const PowerUp& powerUp : powerUps)
    {
        if (powerUp.activated)
            if (powerUp.type == type)
                return true;
    }

    return false;
}