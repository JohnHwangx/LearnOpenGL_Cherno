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
		Geometry(const Texture* texture);
		virtual ~Geometry();

		void Draw();
		void BindShader(Shader& shader);
		void SetTransform(const glm::mat4& transform);

	protected:
		virtual GeometryData* MakeGeometryData() = 0;

		inline bool HasTexture() const { return m_Texture != nullptr; }

	protected:
		const Texture* m_Texture;
	};
}