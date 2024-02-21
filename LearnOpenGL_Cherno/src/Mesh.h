#pragma once

#include <vector>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

class Mesh
{
public:
    /*  ��������  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;
    /*  ����  */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
    ~Mesh();
    void Draw(Shader& shader);
    void DrawInstanced(Shader& shader, unsigned int amount);

    void SetInstancedMatrix();

    inline unsigned int GetVAO() { return m_VAO->GetRendererID(); }
private:
    /*  ����  */
    void setupMesh();

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBUffer;
};