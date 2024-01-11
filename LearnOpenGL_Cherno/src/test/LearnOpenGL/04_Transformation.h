#pragma once

#include "test/test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace Test {
	class Part1_Transformation :public Test
	{
	public:
		Part1_Transformation();
		~Part1_Transformation();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Textures[2];

		float m_Position[2] = { 0.5f, -0.5f };
		float m_CombineValue = 0.5;
	};
}