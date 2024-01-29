#pragma once
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Screen
{
public:
	Screen(Shader& shader, Texture& texture);
	~Screen();

	void Draw();
private:
	//unsigned int m_TextureId;
	Texture* m_Texture;
	Shader* m_Shader;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBUffer;
	//std::unique_ptr<Texture> m_Texture;
};