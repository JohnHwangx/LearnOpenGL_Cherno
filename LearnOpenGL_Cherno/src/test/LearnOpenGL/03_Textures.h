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
		unsigned int GetTexture(const std::string& path);

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;
		//std::unique_ptr<Texture> m_Texture;

		unsigned int m_TextureIds[3];
		int m_Width, m_Height, m_BPP;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;

		float m_Scale;
		int m_WrapIndex, m_MagFilterIndex, m_MinFilterIndex;
		int m_TextureIndex;
	};
}