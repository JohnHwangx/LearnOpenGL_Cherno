#include "Cube.h"
#include "VertexBufferLayout.h"

Cube::Cube(Shader& shader)
{
	float vertices[] = {
		//---- Œª÷√ ----		  // texCoords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,

		-0.5f, -0.5f, -0.5f, -0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -0.0f,  1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  1.0f,

		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
	};

	unsigned int indices[] = {
		// select the top left image
		0, 1, 2,
		1, 3, 2,
		// select the top middle image
		0 + 4, 1 + 4, 2 + 4,
		1 + 4, 3 + 4, 2 + 4,
		// select to top right image
		0 + 8, 1 + 8, 2 + 8,
		1 + 8, 3 + 8, 2 + 8,
		// select the bottom left image
		0 + 12, 1 + 12, 2 + 12,
		1 + 12, 3 + 12, 2 + 12,
		// select the bottom middle image
		0 + 16, 1 + 16, 2 + 16,
		1 + 16, 3 + 16, 2 + 16,
		// select the bottom right image
		0 + 20, 1 + 20, 2 + 20,
		1 + 20, 3 + 20, 2 + 20,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * (3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(indices, 36);
	m_Texture = std::make_unique<Texture>("res/textures/marble.jpg");

	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	m_Texture->Bind();
	Renderer renderer;
	renderer.DrawElement(*m_VAO, *m_IndexBUffer, *m_Shader);
}

void Cube::SetTransform(const glm::mat4& transform)
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_Model", transform);
}
