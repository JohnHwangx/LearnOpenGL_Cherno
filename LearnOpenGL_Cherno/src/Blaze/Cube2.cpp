#include "Cube2.h"

namespace Blaze {

	Cube2::Cube2(float width, float height, float depth)
		:m_Width(width), m_Height(height), m_Depth(depth)
	{
		Blaze::GeometryData* data = MakeGeometryData();
		m_CubeVAO.reset(data->MakeStaticVAO());
	}

	Cube2::~Cube2()
	{
	}

	/*
				   /3--------/7
				  / |       / |
				 /  |      /  |
				1---------5   |
				|  /2- - -|- -6
				| /       |  /
				|/        | /
				0---------4/

	*/
	GeometryData* Cube2::MakeGeometryData()
	{
		float halfWidth = m_Width / 2.0f;
		float halfHeight = m_Height / 2.0f;
		float halfDepth = m_Depth / 2.0f;

		GeometryData* data = new GeometryData();
		//0
		data->m_Positions.push_back({ -halfWidth, -halfHeight, halfDepth });
		data->m_TexCoords.push_back({ 1, 0 });
		//1
		data->m_Positions.push_back({ -halfWidth, halfHeight, halfDepth });
		data->m_TexCoords.push_back({ 1, 1 });
		//2
		data->m_Positions.push_back({ -halfWidth, -halfHeight, -halfDepth });
		data->m_TexCoords.push_back({ 0, 0 });
		//3
		data->m_Positions.push_back({ -halfWidth, halfHeight, -halfDepth });
		data->m_TexCoords.push_back({ 0, 1 });
		//4
		data->m_Positions.push_back({ halfWidth, -halfHeight, halfDepth });
		data->m_TexCoords.push_back({ 0, 0 });
		//5
		data->m_Positions.push_back({ halfWidth, halfHeight, halfDepth });
		data->m_TexCoords.push_back({ 0, 1 });
		//6
		data->m_Positions.push_back({ halfWidth, -halfHeight, -halfDepth });
		data->m_TexCoords.push_back({ 1, 0 });
		//7
		data->m_Positions.push_back({ halfWidth, halfHeight, -halfDepth });
		data->m_TexCoords.push_back({ 1, 1 });

		// 法线朝外
		data->m_Indices = { 0, 1, 3, 0, 3, 2 }; // 左面
		data->m_Indices.insert(data->m_Indices.end(), { 3, 7, 6, 3, 6, 2 }); // 后面
		data->m_Indices.insert(data->m_Indices.end(), { 6, 7, 5, 6, 5, 4 }); // 右面
		data->m_Indices.insert(data->m_Indices.end(), { 5, 1, 0, 5, 0, 4 }); // 前面
		data->m_Indices.insert(data->m_Indices.end(), { 1, 5, 7, 1, 7, 3 }); // 上面
		data->m_Indices.insert(data->m_Indices.end(), { 2, 6, 4, 2, 4, 0 }); // 下面

		return data;
	}

	void Cube2::Draw()
	{
		m_CubeVAO->Draw();
	}
}