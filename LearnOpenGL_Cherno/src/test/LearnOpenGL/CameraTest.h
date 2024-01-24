#pragma once

#include "test/Test.h"
#include "Camera.h"

namespace Test {
	class CameraTest : public Test
	{
	public:
		CameraTest();
		~CameraTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		virtual void OnImGuiRender();

	protected:
		std::unique_ptr<Camera> m_Camera;

		bool m_IsOthor = false;
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Distance = 3.0f;
	};

}