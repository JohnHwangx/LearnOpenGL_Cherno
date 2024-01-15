#include "Light.h"

Light::Light()
	: m_Ambient{ 0.2f, 0.2f, 0.2f },m_Diffuse{ 0.5f, 0.5f, 0.5f }, m_Spacular{ 1.0f, 1.0f, 1.0f }
{
}

Light::~Light()
{
}