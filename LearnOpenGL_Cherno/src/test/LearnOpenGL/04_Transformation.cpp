#include "04_Transformation.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace Test {

	Part1_Transformation::Part1_Transformation()
	{
		float vertices[] = {
			//---- 位置 ----      ---- 颜色 ----     - 纹理坐标 -
		   -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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
		glm::mat4 trans = glm::mat4(1.0f);;
		trans = glm::translate(trans, glm::vec3(m_Position[0], m_Position[1], 0.0f));
		trans = glm::rotate(trans, deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		m_Shader->SetUniformMat4f("transform", trans);

		m_Shader->SetUniform1f("mixValue", m_CombineValue);
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
		ImGui::DragFloat2("Position: ", m_Position, 0.1f, -1, 1);
		ImGui::DragFloat("Combine Value: : ", &m_CombineValue, 0.05f, 0, 1);

	}
}