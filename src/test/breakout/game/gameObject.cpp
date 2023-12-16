#include "./gameObject.h"

GameObject::GameObject() : position{0.0f}, size{1.0f}, velocity{0.0f},
                           color{1.0f}, rotation{0.0f}, isSolid{false}, destroyed{false},
                           texture{Texture()} {}
GameObject::GameObject(glm::vec2 _position, glm::vec2 _size, Texture _texture,
                       glm::vec3 _color, glm::vec2 _velocity) : position{_position}, size{_size}, velocity{_velocity},
                                                                color{_color}, rotation{0.0f}, isSolid{false}, destroyed{false},
                                                                texture{_texture} {}

void GameObject::draw(Sprite2D &sprite)
{
    sprite.draw(texture, position, size, rotation, color);
}