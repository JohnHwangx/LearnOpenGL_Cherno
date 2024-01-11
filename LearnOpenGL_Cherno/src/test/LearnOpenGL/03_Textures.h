#pragma once
#include "test/test.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace Test {
	class Part1_Textures :public Test
	{
	public:
		Part1_Textures();
		~Part1_Textures();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Textures[3];

		float m_Scale;
		int m_WrapIndex, m_MagFilterIndex, m_MinFilterIndex;
		int m_TextureIndex;
	};
}