#include "05_CoordinationSystem.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace Test {

	Part1_CoodinationSystem::Part1_CoodinationSystem()
	{
		float vertices[] = {
			//---- 位置 ----      ---- 颜色 ----     - 纹理坐标 -
			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上

			-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上

			-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上

			 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上
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
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 8 * 4 * 6);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IB = std::make_unique<IndexBuffer>(indices, 36);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_CoordinationSystem.shader");

		m_Textures[0] = std::make_unique<Texture>("res/textures/awesomeface.png");
		m_Textures[1] = std::make_unique<Texture>("res/textures/container.jpg");

		//int samplers[2] = { 0, 1 };
		m_Shader->Bind();
		m_Shader->SetUniform1i("uTexture1", 0);
		m_Shader->SetUniform1i("uTexture2", 1);

		m_Textures[0]->Bind();
		m_Textures[1]->Bind(1);

		GLCall(glEnable(GL_DEPTH_TEST));
	}

	Part1_CoodinationSystem::~Part1_CoodinationSystem()
	{
	}

	void Part1_CoodinationSystem::OnUpdate(float deltaTime)
	{
		glm::mat4 model(1.0f);
		/*model = glm::rotate(model, glm::radians(m_Fov), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));*/
		model = glm::rotate(model, deltaTime, glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view(1.0f);		
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));// 注意，我们将矩阵向我们要进行移动场景的反方向移动。

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		m_Shader->SetUniformMat4f("model", model);
		m_Shader->SetUniformMat4f("view", view);
		m_Shader->SetUniformMat4f("projection", projection);
	}

	void Part1_CoodinationSystem::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_Shader->SetUniform1f("mixValue", m_CombineValue);		

		Renderer renderer;
		renderer.DrawElement(*m_VAO, *m_IB, *m_Shader);
	}

	void Part1_CoodinationSystem::OnImGuiRender()
	{
		ImGui::DragFloat("Combine Value", &m_CombineValue, 0.05f, 0, 1);
		ImGui::Checkbox("Demo Window", &m_IsOthor);
		ImGui::DragFloat("Fov", &m_Fov, 1.0f, -180.0f, 180.0f);
	}
}