#include "./game.h"

typedef std::tuple<bool, Direction, glm::vec2> Collision;
Collision checkCollision(BallObject &one, GameObject &two);
Direction vectorDirection(glm::vec2 target);

Sprite2D *renderer;
GameObject *player;
const glm::vec2 PLAYER_SIZE{100.0f, 20.0f};
const float PLAYER_VELOCITY{500.0f};
BallObject *ball;
const glm::vec2 INITIAL_BALL_VELOCITY{100.0f, -350.0f};
const float BALL_RADIUS = 12.5f;
Particle2DGenerator *particles;
GamePostProcessing *effects;
float shakeTime = 0.0f;

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), keys(),
                                                      width(width), height(height) {}
Game::~Game()
{
    delete renderer;
    delete player;
    delete ball;
    delete particles;
    delete effects;
}

void Game::init()
{
    srand(time(NULL));

    ResourceManager::LoadShader("./shaders/game/game.vert", "./shaders/game/game.frag", "sprite");
    ResourceManager::LoadShader("./shaders/game/particles.vert", "./shaders/game/particles.frag", "particle");
    ResourceManager::LoadShader("./shaders/game/postprocessing.vert",
                                "./shaders/game/postprocessing.frag", "postProcessing");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use();
    ResourceManager::GetShader("sprite").setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);
    ResourceManager::GetShader("particle").use();
    ResourceManager::GetShader("particle").setInt("sprite", 0);
    ResourceManager::GetShader("particle").setMat4("projection", projection);

    ResourceManager::LoadTexture("./assets/textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("./assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("./assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("./assets/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("./assets/textures/particle.png", true, "particle");

    Shader shader{ResourceManager::GetShader("sprite")};
    renderer = new Sprite2D{shader};
    shader = ResourceManager::GetShader("particle");
    Texture texture{ResourceManager::GetTexture("particle")};
    particles = new Particle2DGenerator{shader, texture, 500};
    shader = ResourceManager::GetShader("postProcessing");
    effects = new GamePostProcessing(shader, width, height);

    for (int i = 0; i < 4; i++)
    {
        GameLevel gameLevel;
        std::string path{"./assets/game/level/" + std::to_string(i + 1) + ".lvl"};
        gameLevel.load(path.c_str(), width, height / 2);
        levels.push_back(gameLevel);
    }
    level = 0;

    ResourceManager::LoadTexture("./assets/textures/paddle.png", true, "paddle");
    glm::vec2 pos{(static_cast<float>(width) / 2.0f) - PLAYER_SIZE.x / 2.0f,
                  static_cast<float>(height) - PLAYER_SIZE.y};
    player = new GameObject{pos, PLAYER_SIZE, ResourceManager::GetTexture("paddle")};

    pos = pos + glm::vec2{PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
                          -BALL_RADIUS * 2.0f};
    ball = new BallObject{pos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                          ResourceManager::GetTexture("face")};

    resetLevel();
}
void Game::processInput(float dt)
{
    if (state == GameState::ACTIVE)
    {
        float velocity{PLAYER_VELOCITY * dt};

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

    particles->update(dt, *ball, 2, glm::vec2{ball->radius / 2.0f});

    if (ball->position.y >= height)
    {
        resetLevel();
        resetPlayer();
    }

    if (shakeTime > 0.0f)
    {
        shakeTime -= dt;
        if (shakeTime <= 0.0f)
            effects->shake = false;
    }
}
void Game::render()
{
    if (state == GameState::ACTIVE)
    {
        effects->beginReder();

        renderer->draw(ResourceManager::GetTexture("background"),
                       glm::vec2{0.0f}, glm::vec2{width, height}, 0.0f);

        levels[level].draw(*renderer);
        player->draw(*renderer);
        particles->draw();
        ball->draw(*renderer);

        effects->endRender();
        effects->render(static_cast<float>(glfwGetTime()));
    }
}

void Game::doCollisions()
{
    for (GameObject &box : levels[level].bricks)
    {
        if (box.destroyed)
            continue;

        Collision ballCollisionBox{checkCollision(*ball, box)};
        if (std::get<0>(ballCollisionBox))
        {
            if (!box.isSolid)
                box.destroyed = true;
            else
            {
                shakeTime = 0.05f;
                effects->shake = true;
            }

            Direction direction{std::get<1>(ballCollisionBox)};
            glm::vec2 diffVec{std::get<2>(ballCollisionBox)};

            if (direction == Direction::LEFT || direction == Direction::RIGHT)
            {
                ball->velocity.x = -ball->velocity.x;
                float penetration{ball->radius - std::abs(diffVec.x)};
                if (direction == Direction::LEFT)
                    ball->position.x += penetration;
                else
                    ball->position.x -= penetration;
            }
            else
            {
                ball->velocity.y = -ball->velocity.y;
                float penetration{ball->radius - std::abs(diffVec.y)};
                if (direction == Direction::UP)
                    ball->position.y -= penetration;
                else
                    ball->position.y += penetration;
            }
        }

        Collision ballCollisionPlayer = checkCollision(*ball, *player);
        if (!ball->stuck && std::get<0>(ballCollisionPlayer))
        {
            float centerBoard{player->position.x + player->size.x / 2.0f};
            float distance{(ball->position.x + ball->radius) - centerBoard};
            float percentaje{distance / (player->size.x / 2.0f)};

            float strength{2.0f};
            glm::vec2 oldVelocity{ball->velocity};
            ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentaje * strength;
            ball->velocity.y = std::abs(ball->velocity.y) * -1.0f;
            ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
        }
    }
}
void Game::resetLevel()
{
    for (GameObject &box : levels[level].bricks)
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
}

Collision checkCollision(BallObject &one, GameObject &two)
{
    glm::vec2 center{one.position + one.radius};

    glm::vec2 aabbHalfExtends{two.size.x / 2.0f, two.size.y / 2.0f};
    glm::vec2 aabbCenter{two.position.x + aabbHalfExtends.x,
                         two.position.y + aabbHalfExtends.y};

    glm::vec2 difference{center - aabbCenter};
    glm::vec2 clamped{glm::clamp(difference, -aabbHalfExtends, aabbHalfExtends)};

    glm::vec2 closet{aabbCenter + clamped};

    difference = closet - center;
    if (glm::length(difference) <= one.radius)
        return std::make_tuple(true, vectorDirection(difference), difference);
    else
        return std::make_tuple(false, Direction::UP, glm::vec2{0.0f});
}
Direction vectorDirection(glm::vec2 target)
{
    glm::vec2 compass[]{
        glm::vec2{0.0f, 1.0f},
        glm::vec2{1.0f, 0.0f},
        glm::vec2{0.0f, -1.0f},
        glm::vec2{-1.0f, 0.0f}};
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