#include "Transparent.h"

#include "VertexBufferLayout.h"

Transparent::Transparent(const std::string& texturepath, Shader& shader)
{
	float transparentVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 1.0f,  0.5f,  0.0f,  1.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,  0.0f, 0.0f,
		 0.0f, -0.5f,  0.0f,  0.0f, 1.0f,
		 1.0f, -0.5f,  0.0f,  1.0f, 1.0f
	};

	unsigned int transparentIndex[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(transparentVertices, sizeof(float) * (3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(transparentIndex, 6);
	m_Texture = std::make_unique<Texture>(texturepath);

	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}

Transparent::~Transparent()
{
}

void Transparent::Draw()
{
	m_Texture->Bind();
	Renderer renderer;
	renderer.DrawElement(*m_VAO, *m_IndexBUffer, *m_Shader);
}


void Transparent::SetTransform(const glm::mat4& transform)
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_Model", transform);
}
