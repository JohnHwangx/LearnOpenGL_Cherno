#pragma once

#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "GeometryData.h"

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
		virtual GeometryData* MakeGeometryData() = 0;

		inline bool HasTexture() const { return m_Texture->GetRendererId() != 0; }

	protected:
		std::unique_ptr<Texture> m_Texture;
	};
}