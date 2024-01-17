#pragma once
#include "test/Test.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"

namespace Test {
	class Part3_LoadingModel :public Test
	{
	public:
		Part3_LoadingModel();
		~Part3_LoadingModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Distance = 3.0f;

		std::unique_ptr<Model> m_Model;
		std::shared_ptr<Shader> m_Shader;
		std::unique_ptr<Camera> m_Camera;
	};
}