#include "Triangle.h"

namespace Blaze {
	Triangle::Triangle()
	{
	}
	Triangle::~Triangle()
	{
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