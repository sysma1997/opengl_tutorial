#pragma once
#define MAX_BONE_INFLUENCE 4

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Shader/Shader.h"
#include "../libs/stb_image.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    int m_BoneIds[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};
struct TextureMesh
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
private:
    unsigned int VBO, EBO;

    void setup();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureMesh> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<TextureMesh> textures);

    void draw(Shader& shader);
};