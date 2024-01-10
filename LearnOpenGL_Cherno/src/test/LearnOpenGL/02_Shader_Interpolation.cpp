#include "02_Shader_Interpolation.h"

namespace Test {

	Part1_Shader_Interpolation::Part1_Shader_Interpolation()
	{
		float vertices[] = {
			// 位置              // 颜色
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 6 * 3);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Shader_Interpolation.shader");
	}

	Part1_Shader_Interpolation::~Part1_Shader_Interpolation()
	{
	}

	void Part1_Shader_Interpolation::OnUpdate(float deltaTime)
	{
	}

	void Part1_Shader_Interpolation::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		renderer.DrawArray(*m_VAO, *m_Shader, 3);
	}

	void Part1_Shader_Interpolation::OnImGuiRender()
	{
	}
}