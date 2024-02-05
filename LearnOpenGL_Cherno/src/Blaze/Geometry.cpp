#include "Geometry.h"

namespace Blaze {

	Geometry::Geometry(const Texture* texture)
	{
		m_Texture = texture;
	}

	Geometry::~Geometry()
	{
	}

	void Geometry::Draw()
	{
	}

	void Geometry::BindShader(Shader& shader)
	{
	}

	void Geometry::SetTransform(const glm::mat4& transform)
	{
	}

}