#pragma once
#include "CameraTest.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Texture.h"
#include "Cube.h"
#include "Plane.h"
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
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Screen> m_Screen;

		std::unique_ptr<Shader> m_SimpleDepthShader;
		std::unique_ptr<Shader> m_DebugDepthQuadShader;
		std::unique_ptr<Framebuffer> m_Framebuffer;
	};
}