#pragma once
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Plane
{
public:
	Plane(Shader& shader);
	Plane(const std::string& texturePath, Shader& shader);
	Plane(float width, const std::string& texturePath);
	Plane(float width, const std::string& texturePath, Shader& shader);
	~Plane();

	void Draw();
	void BindShader(Shader& shader);
	void SetTransform(const glm::mat4& transform);
private:
	Shader* m_Shader;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBUffer;
	std::unique_ptr<Texture> m_Texture;
};