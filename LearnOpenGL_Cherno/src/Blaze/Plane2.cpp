#include "Plane2.h"

namespace Blaze {
	Plane::Plane(float width, float height, const std::string& texturePath)
		:Geometry(texturePath), m_Width(width), m_Height(height)
	{
		GeometryData* data = MakeGeometryData();
		m_PlaneVAO.reset(data->MakeStaticVAO(true));
	}

	Plane::~Plane()
	{
	}

	void Plane::Draw()
	{
		if (HasTexture())
			m_Texture->Bind();

		m_PlaneVAO->Draw();
	}

	GeometryData* Plane::MakeGeometryData()
	{
		float halfWidth = m_Width / 2.0f;
		float halfHeight = m_Height / 2.0f;

		GeometryData* data = new GeometryData();

		data->m_Positions.push_back({ -halfWidth, 0.0f, -halfHeight });
		data->m_Positions.push_back({ -halfWidth, 0.0f,  halfHeight });
		data->m_Positions.push_back({  halfWidth, 0.0f, -halfHeight });
		data->m_Positions.push_back({  halfWidth, 0.0f,  halfHeight });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 1.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  m_Height });
		data->m_TexCoords.push_back({ m_Width,  0.0f });
		data->m_TexCoords.push_back({ m_Width,  m_Height });

		data->m_Indices = { 0, 1, 2, 1, 3, 2 };

		return data;
	}
}