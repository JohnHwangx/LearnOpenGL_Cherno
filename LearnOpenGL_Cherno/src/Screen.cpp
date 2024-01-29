#include "Screen.h"
#include "VertexBufferLayout.h"

Screen::Screen(Shader& shader, const unsigned int textureId)
    :m_TextureId(textureId)
{
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates. NOTE that this plane is now much smaller and at the top of the screen
        // positions   // texCoords
        -0.8f,  0.8f,  0.0f, 1.0f,
        -0.8f, -0.8f,  0.0f, 0.0f,
         0.8f, -0.8f,  1.0f, 0.0f,
         0.8f,  0.8f,  1.0f, 1.0f
    };

    unsigned int quadIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    m_VAO = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(quadVertices, sizeof(float) * (2 + 2) * 4 * 6);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_IndexBUffer = std::make_unique<IndexBuffer>(quadIndices, 6);

    m_Shader = &shader;
    m_Shader->Bind();
    m_Shader->SetUniform1i("screenTexture", 0);
}

Screen::~Screen()
{
}

void Screen::Draw()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
    Renderer renderer;
    renderer.DrawElement(*m_VAO, *m_IndexBUffer, *m_Shader);
}
