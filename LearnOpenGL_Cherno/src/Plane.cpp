#include "Plane.h"
#include "VertexBufferLayout.h"

Plane::Plane(Shader& shader)
{
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	unsigned int planeIndex[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(planeVertices, sizeof(float) * (3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(planeIndex, 6);
	m_Texture = std::make_unique<Texture>("res/textures/metal.png");

	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}

Plane::Plane(const std::string& texturePath, Shader& shader)
{
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	unsigned int planeIndex[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(planeVertices, sizeof(float) * (3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(planeIndex, 6);
	m_Texture = std::make_unique<Texture>(texturePath);

	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}

Plane::Plane(float width, const std::string& texturePath)
{
	float planeVertices[] = {
		// positions								// texture Coords
		 width, -0.5f,  width,  0.0f, 1.0f, 0.0f,  width, 0.0f,
		-width, -0.5f,  width,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-width, -0.5f, -width,  0.0f, 1.0f, 0.0f,  0.0f, width,
		 width, -0.5f, -width,  0.0f, 1.0f, 0.0f,  width, width
	};

	unsigned int planeIndex[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(planeVertices, sizeof(float) * (3 + 3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(planeIndex, 6);
	m_Texture = std::make_unique<Texture>(texturePath);
}

Plane::Plane(float width, const std::string& texturePath, Shader& shader)
{
	float planeVertices[] = {
		// positions								// texture Coords
		 width, -0.5f,  width,  0.0f, 1.0f, 0.0f,  width, 0.0f,
		-width, -0.5f,  width,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-width, -0.5f, -width,  0.0f, 1.0f, 0.0f,  0.0f, width,
		 width, -0.5f, -width,  0.0f, 1.0f, 0.0f,  width, width
	};

	unsigned int planeIndex[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(planeVertices, sizeof(float) * (3 + 3 + 2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBUffer = std::make_unique<IndexBuffer>(planeIndex, 6);
	m_Texture = std::make_unique<Texture>(texturePath);

	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}

Plane::~Plane()
{
}

void Plane::Draw()
{
	m_Texture->Bind();
	Renderer renderer;
	renderer.DrawElement(*m_VAO, *m_IndexBUffer, *m_Shader);
}

void Plane::BindShader(Shader& shader)
{
	m_Shader = &shader;
	m_Shader->Bind();
	m_Shader->SetUniform1i("texture_diffuse1", 0);
}


void Plane::SetTransform(const glm::mat4& transform)
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_Model", transform);
}
