#pragma once

#include "CameraTest.h"
#include "Cube.h"
#include "Plane.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Test {
	class Part4_DepthTesting: public CameraTest
	{
	public:
		Part4_DepthTesting();
		~Part4_DepthTesting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Shader> m_Shader;
	};
}