#include "Triangle.h"

namespace Blaze {

	Triangle::Triangle()
	{
		Blaze::GeometryData* data = MakeGeometryData();
		m_TriangleVAO.reset(data->MakeStaticVAO());
	}

	Triangle::~Triangle()
	{
	}

	void Triangle::Draw()
	{
		m_TriangleVAO->Draw();
	}

	GeometryData* Triangle::MakeGeometryData()
	{
		GeometryData* data = new GeometryData();
		data->m_Positions.push_back({ -0.5f, -0.5f, 0.0f });
		data->m_Positions.push_back({ 0.5f, -0.5f, 0.0f });
		data->m_Positions.push_back({ 0.0f, 0.5f, 0.0f });
		data->m_Indices = { 0, 1, 2 };
		return data;
	}
}