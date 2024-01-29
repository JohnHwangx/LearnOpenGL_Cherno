#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"

struct BoundingBox
{
    glm::vec3 Min;
    glm::vec3 Max;

    BoundingBox()
    {
        Min = glm::vec3(FLT_MAX);
        Max = glm::vec3(-FLT_MAX);
    }

    void SetBoundingBox(float x, float y, float z)
    {
        if (Min.x > x)
            Min.x = x;
        if (Min.y > y)
            Min.y = y;
        if (Min.z > z)
            Min.z = z;
        if (Max.x < x)
            Max.x = x;
        if (Max.y < y)
            Max.y = y;
        if (Max.z < z)
            Max.z = z;
    }

    glm::vec3 GetCenter() const
    {
        return glm::vec3(
            (Min.x + Max.x) / 2.0f,
            (Min.y + Max.y) / 2.0f,
            (Min.z + Max.z) / 2.0f
        );
    }
};

class Model
{
public:
    /*  函数   */
    Model(const std::string& path, bool gamma = false): gammaCorrection(gamma)
    {        
        loadModel(path);
    }
    ~Model();
    void Draw();
    void BindShader(Shader& shader);

    void SetTransform(const glm::mat4& transform);
public:
    BoundingBox m_BBox;

private:
    /*  模型数据  */
    std::vector<Texture*> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh*> meshes;
    Shader* m_Shader;
    std::string directory;
    bool gammaCorrection;
    /*  函数   */
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};