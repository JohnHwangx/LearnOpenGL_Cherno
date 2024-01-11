#include "04_Transformation.h"

namespace Test {

	Part1_Transformation::Part1_Transformation()
	{
		float vertices[] = {
			//---- λ�� ----      ---- ��ɫ ----     - �������� -
		   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 8 * 4);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IB = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Transformation.shader");

		m_Textures[0] = std::make_unique<Texture>("res/textures/awesomeface.png");
		m_Textures[1] = std::make_unique<Texture>("res/textures/container.jpg");

		//int samplers[2] = { 0, 1 };
		m_Shader->Bind();
		m_Shader->SetUniform1i("uTexture1", 0);
		m_Shader->SetUniform1i("uTexture2", 1);
	}

	Part1_Transformation::~Part1_Transformation()
	{
	}

	void Part1_Transformation::OnUpdate(float deltaTime)
	{
	}

	void Part1_Transformation::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_Textures[0]->Bind();
		m_Textures[1]->Bind(1);

		Renderer renderer;
		renderer.DrawElement(*m_VAO, *m_IB, *m_Shader);
	}

	void Part1_Transformation::OnImGuiRender()
	{
	}
}