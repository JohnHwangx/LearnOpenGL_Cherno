#include "Geometry.h"

Geometry::Geometry(const std::string& texturePath)
{
	m_Texture = std::make_unique<Texture>(texturePath);
}

Geometry::~Geometry()
{
}

void Geometry::BindData(const float* vertices, const unsigned int* indices)
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
