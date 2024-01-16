#pragma once

#include <vector>
#include <assimp/config.h>
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
    /*  ����   */
    Model(char* path)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    /*  ģ������  */
    std::vector<Mesh> meshes;
    std::string directory;
    /*  ����   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
};