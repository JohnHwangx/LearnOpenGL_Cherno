#pragma once

#include "test/Test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <Camera.h>

namespace Test {
	class Part2_BasicLighting:public Test
	{
	public:
		Part2_BasicLighting();
		~Part2_BasicLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexArray> m_LightCubeVAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_LightingShader;
		std::unique_ptr<Shader> m_LightCubeShader;
		std::unique_ptr<Camera> m_Camera;

		bool m_IsOthor = false;
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Distance = 3.0f;
		glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	};
}