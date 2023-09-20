#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader/Shader.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoords;
};
struct TextureMesh
{
    unsigned int id;
    std::string type;
};

class Mesh
{
private:
    unsigned int VAO, VBO, EBO;

    void setup();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureMesh> textures;

    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<TextureMesh> textures);
    void draw(Shader &shader);
};