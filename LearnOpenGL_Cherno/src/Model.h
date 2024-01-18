#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
    /*  ����   */
    Model(const std::string& path, bool gamma = false): gammaCorrection(gamma)
    {
        loadModel(path);
    }
    ~Model();
    void Draw(Shader& shader);
private:
    /*  ģ������  */
    std::vector<Texture*> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh*> meshes;
    std::string directory;
    bool gammaCorrection;
    /*  ����   */
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};