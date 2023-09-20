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

class Model
{
private:
    std::vector<Mesh> meshes;
    std::string directory;

    void load(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<TextureMesh> loadMaterialTextures(aiMaterial *mat,
                                                  aiTextureType type,
                                                  std::string typeName);

public:
    Model(char *path);

    void draw(Shader &shader);
};