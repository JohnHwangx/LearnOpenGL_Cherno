#pragma once
#include "CameraTest.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Texture.h"
#include "Blaze/Cube2.h"
#include "Blaze/Plane2.h"
#include "Transparent.h"
#include "Framebuffer.h"
#include "Screen.h"

namespace Test {

	class Part5_ShadowMapping : public CameraTest
	{
	public:
		Part5_ShadowMapping();
		~Part5_ShadowMapping();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		void DrawScene(Shader& shader);

	private:
		//std::unique_ptr<Cube> m_Cube;
		//std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Blaze::Cube> m_Cube;
		std::unique_ptr<Blaze::Plane> m_Plane;
		std::unique_ptr<Screen> m_Screen;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_SimpleDepthShader;
		std::unique_ptr<Shader> m_DebugDepthQuadShader;
		std::unique_ptr<Framebuffer> m_Framebuffer;

		glm::vec3 m_LightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
	};
}