#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./Mesh.h"
#include "../shader/Shader.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
private:
    void load(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<TextureMesh> loadMaterialTextures(aiMaterial *mat,
                                                  aiTextureType type,
                                                  std::string typeName);

public:
    std::vector<TextureMesh> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model(std::string path);

    void draw(Shader &shader);
};