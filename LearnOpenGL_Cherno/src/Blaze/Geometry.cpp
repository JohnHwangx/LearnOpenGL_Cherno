#include "Geometry.h"

namespace Blaze {

	Geometry::Geometry(const std::string& texturePath)
	{
		m_Texture = std::make_unique<Texture>(texturePath);

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