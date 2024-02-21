#include <GL/glew.h>
#include "Mesh.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i]->GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        shader.SetUniform1i(name + number, i);
        // and finally bind the texture
        textures[i]->Bind(i);
    }
    Renderer renderer;
    renderer.DrawElement(*m_VAO, *m_IndexBUffer, shader);
}

void Mesh::DrawInstanced(Shader& shader, unsigned int amount)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i]->GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        shader.SetUniform1i(name + number, i);
        // and finally bind the texture
        textures[i]->Bind(i);
    }
    Renderer renderer;
    renderer.DrawInstanced(*m_VAO, *m_IndexBUffer, shader, amount);
}

void Mesh::SetInstancedMatrix()
{

}

void Mesh::setupMesh()
{
    m_VAO = std::make_unique<VertexArray>();
    unsigned int verticesByte = vertices.size() * sizeof(Vertex);
    m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], verticesByte);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(3);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    unsigned int indicesByte = indices.size();
    m_IndexBUffer = std::make_unique<IndexBuffer>(&indices[0], indicesByte);
}
