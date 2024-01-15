#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(Shader& shader)
	:m_Shader(shader)
{
	m_Light = std::make_unique<Light>();
}

BasicMaterial::~BasicMaterial()
{
	std::cout << "Material Distribute~\n";
}

void BasicMaterial::SetAmbient(float r, float g, float b)
{
	m_Shader.SetUniform3f("material.ambient", r, g, b);
}

void BasicMaterial::SetDiffuse(float r, float g, float b)
{
	m_Shader.SetUniform3f("material.diffuse", r, g, b);
}

void BasicMaterial::SetSpecular(float r, float g, float b)
{
	m_Shader.SetUniform3f("material.specular", r, g, b);
}

void BasicMaterial::SetShininess(float value)
{
	m_Shader.SetUniform1f("material.shininess", value);
}

void BasicMaterial::SetLightAmbient(float r, float g, float b)
{
	m_Shader.SetUniform3f("light.ambient", r, g, b);
}

void BasicMaterial::SetLightAmbient(glm::vec3 ambient)
{
	m_Shader.SetUniform3fv("light.ambient", ambient);
}

void BasicMaterial::SetLightDiffuse(glm::vec3 diffuse)
{
	m_Shader.SetUniform3fv("light.diffuse", diffuse);
}

void BasicMaterial::SetLightDiffuse(float r, float g, float b)
{
	m_Shader.SetUniform3f("light.diffuse", r, g, b);
}

void BasicMaterial::SetLightSpecular(glm::vec3 specular)
{
	m_Shader.SetUniform3fv("light.specular", specular);
}

void BasicMaterial::SetLightSpecular(float r, float g, float b)
{
	m_Shader.SetUniform3f("light.specular", r, g, b);
}

void BasicMaterial::SetLightPosition(glm::vec3 lightPos)
{
	m_Shader.SetUniform3fv("light.position", lightPos);
}
