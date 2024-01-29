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

	class Part4_FrameBuffer : public CameraTest
	{
	public:
		Part4_FrameBuffer();
		~Part4_FrameBuffer();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Transparent> m_Grass;
		std::unique_ptr<Transparent> m_Window;
		std::unique_ptr<Screen> m_Screen;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_ScreenShader;
		std::unique_ptr<Framebuffer> m_Framebuffer;
	};
}