#pragma once

#include "CameraTest.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Texture.h"
#include "Cube.h"
#include "Plane.h"

namespace Test {
	class Part4_StencilTesting : public CameraTest
	{
	public:
		Part4_StencilTesting();
		~Part4_StencilTesting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Cube> m_StencilCube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_StencilSingleShader;
	};
}