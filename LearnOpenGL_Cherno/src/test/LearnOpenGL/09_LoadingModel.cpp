#include "09_LoadingModel.h"
#include <GL/glew.h>
#include "imgui/imgui.h"

namespace Test{

	Part3_LoadingModel::Part3_LoadingModel()
	{
		glEnable(GL_DEPTH_TEST);
		m_Model = std::make_unique<Model>("res/models/nanosuit/nanosuit.obj");
		m_Shader = std::make_shared<Shader>("res/shader/Part3_ModelLoading.shader");

		glm::vec3 modelCenter = m_Model->m_BBox.GetCenter();
		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

		m_Model->BindShader(*(m_Shader.get()));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, -modelCenter);
		m_Model->SetTransform(model);
	}

	Part3_LoadingModel::~Part3_LoadingModel()
	{
	}

	void Part3_LoadingModel::OnUpdate(float deltaTime)
	{
	}

	void Part3_LoadingModel::OnRender()
	{
		glClearColor(0.3f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Shader->Bind();

		glm::mat4 view = m_Camera->GetViewMatrix();

		//glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		//m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Projection", projection);
		m_Model->Draw();
	}

	void Part3_LoadingModel::OnImGuiRender()
	{
		if (ImGui::DragFloat("Yaw", &m_Yaw, 1.0f, -180.0f, 180.0f))
		{
			m_Camera->CameraYaw(m_Yaw);
		}

		if (ImGui::DragFloat("Pitch", &m_Pitch, 1.0f, -89.9f, 89.9f))
		{
			m_Camera->CameraPitch(m_Pitch);
		}

		if (ImGui::DragFloat("Distance", &m_Distance, 0.1f, 0.1f, 30.0f))
		{
			m_Camera->SetDistance(m_Distance);
		}
	}
}
