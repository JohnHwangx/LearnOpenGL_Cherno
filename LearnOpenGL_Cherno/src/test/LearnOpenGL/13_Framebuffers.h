#pragma once

#include "CameraTest.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Texture.h"
#include "Cube.h"
#include "Plane.h"
#include "Transparent.h"

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
		std::unique_ptr<Shader> m_Shader;

		// transparent vegetation locations
		// --------------------------------
		std::vector<glm::vec3> vegetation
		{
			glm::vec3(-1.5f, 0.0f, -0.48f),
			glm::vec3(1.5f, 0.0f, 0.51f),
			glm::vec3(0.0f, 0.0f, 0.7f),
			glm::vec3(-0.3f, 0.0f, -2.3f),
			glm::vec3(0.5f, 0.0f, -0.6f)
		};
		std::vector<glm::vec3> windows
		{
			glm::vec3(-1.5f, 0.0f, -0.43f),
			glm::vec3(1.5f, 0.0f, 0.55f),
			glm::vec3(0.0f, 0.0f, 0.3f),
			glm::vec3(-0.3f, 0.0f, -2.6f),
			glm::vec3(0.5f, 0.0f, -0.3f)
		};
	};
}