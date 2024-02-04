#pragma once

#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

namespace Blaze {
	class Geometry
	{
	public:
		Geometry(const std::string& texturePath);
		virtual ~Geometry();

		void Draw();
		void BindShader(Shader& shader);
		void SetTransform(const glm::mat4& transform);

	protected:
		void BindData(const float* vertices, const unsigned int* indices);
	private:

		Shader* m_Shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Texture> m_Texture;
	};
}