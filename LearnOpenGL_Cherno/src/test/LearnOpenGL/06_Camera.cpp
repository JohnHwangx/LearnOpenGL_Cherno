#include "06_Camera.h"
#include "imgui/imgui.h"

namespace Test {

	Part1_Camera::Part1_Camera()
	{
		float vertices[] = {
			//---- 位置 ----      ---- 颜色 ----     - 纹理坐标 -
			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上

			-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上

			-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上

			 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // 右上
			 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 右下
			 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // 左上
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

		m_Camera = std::make_unique<Camera>();

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

	Part1_Camera::~Part1_Camera()
	{
	}

	void Part1_Camera::OnUpdate(float deltaTime)
	{
		//float camX = sin(m_Yaw) * cos(glm::radians(m_Pitch));
		//float camY = sin(glm::radians(m_Pitch));
		//float camZ = cos(m_Yaw) * cos(glm::radians(m_Pitch));
		//glm::mat4 view(1.0f);
		//view = glm::lookAt(glm::vec3(camX, camY, camZ) * m_PersDistance, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//view = glm::scale(view, glm::vec3(m_Distance));

		//float camX = cos(glm::radians(-90.0f)) * cos(glm::radians(0.0f)) * m_PersDistance;
		//float camY = sin(glm::radians(0.0f)) * m_PersDistance;
		//float camZ = sin(glm::radians(-90.0f)) * cos(glm::radians(0.0f)) * m_PersDistance;
		//glm::mat4 view(1.0f);
		//view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//view = glm::scale(view, glm::vec3(m_Distance));

		m_DeltaTime = deltaTime - m_LastFrame;
		m_LastFrame = deltaTime;

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		glm::mat4 view = m_Camera->GetViewMatrix();
		if(m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));
		m_Shader->SetUniformMat4f("view", view);
		m_Shader->SetUniformMat4f("projection", projection);
	}

	void Part1_Camera::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_Shader->SetUniform1f("mixValue", m_CombineValue);

		Renderer renderer;
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, m_CubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			m_Shader->SetUniformMat4f("model", model);

			renderer.DrawElement(*m_VAO, *m_IB, *m_Shader);
		}
	}

	void Part1_Camera::OnImGuiRender()
	{
		ImGui::DragFloat("Combine Value", &m_CombineValue, 0.05f, 0, 1);
		ImGui::Checkbox("Demo Window", &m_IsOthor);
		if (ImGui::DragFloat("Yaw", &m_Yaw, 1.0f, -89.9f, 89.9f))
		{
			m_Camera->CameraYaw(m_Yaw);
		}

		if (ImGui::DragFloat("Pitch", &m_Pitch, 1.0f, -89.9f, 89.9f))
		{
			m_Camera->CameraPitch(m_Pitch);
		}

		if (ImGui::DragFloat(" Distance", &m_Distance, 0.1f, 0.1f, 30.0f))
		{
			m_Camera->SetDistance(m_Distance);
		}

		if (ImGui::Button("W")) {
			m_Camera->CameraTranslation(Camera_Movement::FORWARD, m_DeltaTime);
		}
		if (ImGui::Button("S")) {
			m_Camera->CameraTranslation(Camera_Movement::BACKWARD, m_DeltaTime);
		}
		if (ImGui::Button("A")) {
			m_Camera->CameraTranslation(Camera_Movement::LEFT, m_DeltaTime);
		}
		if (ImGui::Button("D")) {
			m_Camera->CameraTranslation(Camera_Movement::RIGHT, m_DeltaTime);
		}
	}
}