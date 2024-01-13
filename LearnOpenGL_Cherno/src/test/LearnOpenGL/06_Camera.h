#pragma once

#include "test/test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Test {
	class Part1_Camera :public Test
	{
	public:
		Part1_Camera();
		~Part1_Camera();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Texture> m_Textures[2];

		float m_CombineValue = 0.5;
		bool m_IsOthor = false;
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Distance = 3.0f;
		//float m_PersDistance = 3.0f;
		const glm::vec3 m_CubePositions[10] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_CameraSpeed = 0.05f;
		
		float m_DeltaTime = 0.0f; // 当前帧与上一帧的时间差
		float m_LastFrame = 0.0f; // 上一帧的时间
	};
}