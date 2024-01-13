#include "06_Camera.h"
#include "imgui/imgui.h"

namespace Test {

	Part1_Camera::Part1_Camera()
	{
		float vertices[] = {
			//---- λ�� ----      ---- ��ɫ ----     - �������� -
			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����

			-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����

			-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����

			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����

			 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // ����
			 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // ����
			 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // ����
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����
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

	Part1_Camera::~Part1_Camera()
	{
	}

	void Part1_Camera::OnUpdate(float deltaTime)
	{
		//float camX = sin(deltaTime) * cos(glm::radians(m_Fov)) * m_PersDistance;
		//float camY = sin(glm::radians(m_Fov)) * m_PersDistance;
		//float camZ = cos(deltaTime) * cos(glm::radians(m_Fov)) * m_PersDistance;
		//glm::mat4 view(1.0f);
		//view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 view(1.0f);
		view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-m_Distance * 1.5f, m_Distance * 1.5f, -m_Distance, m_Distance, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

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
		ImGui::DragFloat("Fov", &m_Fov, 1.0f, -89.9f, 89.9f);
		if (m_IsOthor == true)
			ImGui::DragFloat("ortho Distance", &m_Distance, 0.1f, 1.0f, 10.0f);
		else
			ImGui::DragFloat("perspective Distance", &m_PersDistance, 0.1f, 0.1f, 30.0f);

		if (ImGui::Button("W")) {
			m_CameraPos += m_CameraSpeed * m_CameraFront;
		}
		if (ImGui::Button("S")) {
			m_CameraPos -= m_CameraSpeed * m_CameraFront;
		}
		if (ImGui::Button("A")) {
			m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
		}
		if (ImGui::Button("D")) {
			m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
		}
	}
}