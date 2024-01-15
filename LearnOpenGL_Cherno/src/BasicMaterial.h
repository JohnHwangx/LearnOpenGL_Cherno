#pragma once

#include <iostream>
#include "Shader.h"
#include "Light.h"

class BasicMaterial {
public:
	BasicMaterial(Shader& shader);
	~BasicMaterial();

	inline void Use()
	{
		m_Shader.Bind();
	}

	void SetAmbient(float r, float g, float b);
	void SetDiffuse(float r, float g, float b);
	void SetSpecular(float r, float g, float b);
	void SetShininess(float value);

	inline const float* GetAmbient() const { return m_Ambient; }
	inline const float* GetDiffuse() const { return m_Diffuse; }
	inline const float* GetSpacular() const { return m_Spacular; }
	inline const float GetShininess() const { return m_Shininess; }

	void SetLightAmbient(glm::vec3);
	void SetLightAmbient(float r, float g, float b);
	void SetLightDiffuse(glm::vec3);
	void SetLightDiffuse(float r, float g, float b);
	void SetLightSpecular(glm::vec3);
	void SetLightSpecular(float r, float g, float b);
	void SetLightPosition(glm::vec3);

	inline const float* GetLightAmbient() const { return m_Light->GetAmbient(); }
	inline const float* GetLightDiffuse() const { return m_Light->GetDiffuse(); }
	inline const float* GetLightSpacular() const { return m_Light->GetSpacular(); }

private:
	float m_Ambient[3];
	float m_Diffuse[3];
	float m_Spacular[3];
	float m_Shininess;

	std::unique_ptr<Light> m_Light;
	Shader m_Shader;
};