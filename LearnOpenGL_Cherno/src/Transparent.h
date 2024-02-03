#pragma once
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Transparent
{
public:
	Transparent(const std::string& texturepath, Shader& shader);
	~Transparent();

	void Draw();
	void SetTransform(const glm::mat4& transform);
private:
	Shader* m_Shader;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBUffer;
	std::unique_ptr<Texture> m_Texture;
};