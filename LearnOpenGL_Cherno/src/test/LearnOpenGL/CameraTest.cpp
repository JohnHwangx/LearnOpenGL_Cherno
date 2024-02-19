#include "CameraTest.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace Test {
	CameraTest::CameraTest()
		:m_IsOthor(false), m_Yaw(0.0f), m_Pitch(0.0f), m_Distance(3.0f)
	{
		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	CameraTest::~CameraTest()
	{
	}

	void CameraTest::OnUpdate(float deltaTime)
	{
	}

	void CameraTest::OnRender()
	{
	}

	void CameraTest::OnImGuiRender()
	{
		ImGui::Checkbox("IsOthor", &m_IsOthor);
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