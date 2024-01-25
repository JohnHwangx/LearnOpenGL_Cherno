#pragma once
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Plane
{
public:
	Plane();
	~Plane();

	void Draw(Shader& shader);
private:

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBUffer;
	std::unique_ptr<Texture> m_Texture;
};