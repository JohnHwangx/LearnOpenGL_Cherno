#pragma once

class Light {
public:
	Light();
	~Light();

	inline void SetAmbient(float r, float g, float b)
	{
		m_Ambient[0] = r;
		m_Ambient[1] = g;
		m_Ambient[2] = b;
	};
	inline void SetDiffuse(float r, float g, float b)
	{
		m_Diffuse[0] = r;
		m_Diffuse[1] = g;
		m_Diffuse[2] = b;
	};
	inline void SetSpecular(float r, float g, float b)
	{
		m_Spacular[0] = r;
		m_Spacular[1] = g;
		m_Spacular[2] = b;
	};

	inline const float* GetAmbient() const { return m_Ambient; }
	inline const float* GetDiffuse() const { return m_Diffuse; }
	inline const float* GetSpacular() const { return m_Spacular; }

private:
	float m_Ambient[3];
	float m_Diffuse[3];
	float m_Spacular[3];

private:

};