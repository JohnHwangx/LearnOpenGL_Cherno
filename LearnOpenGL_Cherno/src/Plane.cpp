#include "Plane.h"
#include "VertexBufferLayout.h"

Plane::Plane()
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
}

Plane::~Plane()
{
}

void Plane::Draw(Shader& shader)
{
	shader.Bind();
	shader.SetUniform1i("texture_diffuse1", 0);

	m_Texture->Bind();
	Renderer renderer;
	renderer.DrawElement(*m_VAO, *m_IndexBUffer, shader);
}
