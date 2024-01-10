#include "03_Textures.h"

namespace Test {

	Part1_Textures::Part1_Textures()
	{
		float vertices[] = {
			 //---- 位置 ----      ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Textures.shader");

		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>("res/textures/container.jpg");
		m_Shader->SetUniform1i("ourTexture", 0);
	}

	Part1_Textures::~Part1_Textures()
	{
	}

	void Part1_Textures::OnUpdate(float deltaTime)
	{
	}

	void Part1_Textures::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();
		renderer.DrawElement(*m_VAO, *m_IB, *m_Shader);
	}

	void Part1_Textures::OnImGuiRender()
	{
	}
}