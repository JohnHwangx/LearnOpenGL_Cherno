#pragma once

#include "test/Test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "Texture.h"
//#include "BasicMaterial.h"

namespace Test {
	class Part2_Material:public Test
	{
	public:
		Part2_Material();
		~Part2_Material();

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
		std::unique_ptr<Texture> m_Textures[2];
		//std::unique_ptr<BasicMaterial> m_BasicMaterial;

		bool m_IsOthor = false;
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Distance = 3.0f;
		float m_LightDistance = 2.0f;
		glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);

		float m_Ambient[3] = { 0.2f, 0.2f, 0.2f };
		float m_Diffuse[3] = { 1.0f, 0.5f, 0.31f };
		float m_Specular[3] = { 0.5f, 0.5f, 0.5f };
		float m_Shininess = 32.0f;
		float m_LightAmbient[3] = { 0.2f, 0.2f, 0.2f };
		float m_LightDiffuse[3] = { 1.0f, 1.0f, 1.0f };
		float m_LightSpecular[3] = { 0.5f, 0.5f, 0.5f };
	};
}