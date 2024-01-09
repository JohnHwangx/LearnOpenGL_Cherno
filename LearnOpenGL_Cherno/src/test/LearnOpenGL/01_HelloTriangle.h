#pragma once

#include "test/Test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace Test {
	class Part1_HelloTriangle :public Test
	{
	public:
		Part1_HelloTriangle();
		~Part1_HelloTriangle();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
	};
}