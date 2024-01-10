#include "test/LearnOpenGL/02_Shader.h"

namespace Test {
	Part1_Shader::Part1_Shader()
	{
		float vertices[] = {
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f   // top 
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 3 * 3);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Shader.shader");
	}

	Part1_Shader::~Part1_Shader()
	{
	}

	void Part1_Shader::OnUpdate(float timeValue)
	{
		m_Shader->Bind();
		// ¸üÐÂuniformÑÕÉ«
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		m_Shader->SetUniform4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
	}

	void Part1_Shader::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));		

		Renderer renderer;
		renderer.DrawArray(*m_VAO, *m_Shader, 3);
	}

	void Part1_Shader::OnImGuiRender()
	{

	}
}