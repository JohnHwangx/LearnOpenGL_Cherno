#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& shaderPath)
{
	m_Shader = std::make_unique<Shader>(shaderPath);
	m_Light = std::make_unique<Light>();
}

BasicMaterial::~BasicMaterial()
{
}

Light::Light()
{
}

Light::~Light()
{
}
