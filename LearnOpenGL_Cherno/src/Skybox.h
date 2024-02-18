#pragma once
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void Draw(const glm::mat4& view, const glm::mat4& projection);

	void BindTexture();

private:
	unsigned int LoadCubemap(const std::vector<std::string>& faces);

private:
	unsigned int m_CubemapTextureID;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBUffer;
	std::unique_ptr<Texture> m_Texture;
};