#pragma once

#include "CameraTest.h"
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
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<IndexBuffer> m_PlaneIB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_PlaneVertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Textures[2];
	};
}