#include "Cube2.h"

namespace Blaze {

	Cube::Cube(const float width, const float height, const float depth, const Texture* texture)
		:Geometry(texture), m_Width(width), m_Height(height), m_Depth(depth)
	{
		Blaze::GeometryData* data = MakeGeometryData();
		m_CubeVAO.reset(data->MakeStaticVAO(true));
	}

	Cube::~Cube()
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
	GeometryData* Cube::MakeGeometryData()
	{
		float halfWidth = m_Width / 2.0f;
		float halfHeight = m_Height / 2.0f;
		float halfDepth = m_Depth / 2.0f;

		GeometryData* data = new GeometryData();
		//0
		data->m_Positions.push_back({ -halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({ -halfWidth,  halfHeight, -halfDepth });
		data->m_Positions.push_back({  halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({  halfWidth,  halfHeight, -halfDepth });
		data->m_Normals.push_back({ 0.0f,  0.0f, -1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, -1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, -1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, -1.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 1.0f, 0.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });
		//1
		data->m_Positions.push_back({ -halfWidth, -halfHeight,  halfDepth });
		data->m_Positions.push_back({  halfWidth, -halfHeight,  halfDepth });
		data->m_Positions.push_back({ -halfWidth,  halfHeight,  halfDepth });
		data->m_Positions.push_back({  halfWidth,  halfHeight,  halfDepth });
		data->m_Normals.push_back({ 0.0f,  0.0f, 1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, 1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, 1.0f });
		data->m_Normals.push_back({ 0.0f,  0.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 1.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });
		//2
		data->m_Positions.push_back({ -halfWidth, halfHeight, -halfDepth });
		data->m_Positions.push_back({ -halfWidth, halfHeight,  halfDepth });
		data->m_Positions.push_back({  halfWidth, halfHeight, -halfDepth });
		data->m_Positions.push_back({  halfWidth, halfHeight,  halfDepth });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Normals.push_back({ 0.0f, 1.0f,  0.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 1.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });
		//3
		data->m_Positions.push_back({ -halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({  halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({ -halfWidth, -halfHeight,  halfDepth });
		data->m_Positions.push_back({  halfWidth, -halfHeight,  halfDepth });
		data->m_Normals.push_back({ 0.0f, -1.0f, 0.0f });
		data->m_Normals.push_back({ 0.0f, -1.0f, 0.0f });
		data->m_Normals.push_back({ 0.0f, -1.0f, 0.0f });
		data->m_Normals.push_back({ 0.0f, -1.0f, 0.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 1.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });
		//4
		data->m_Positions.push_back({ -halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({ -halfWidth, -halfHeight,  halfDepth });
		data->m_Positions.push_back({ -halfWidth,  halfHeight, -halfDepth });
		data->m_Positions.push_back({ -halfWidth,  halfHeight,  halfDepth });
		data->m_Normals.push_back({ -1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ -1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ -1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ -1.0f, 0.0f, 0.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 1.0f, 0.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });
		//5
		data->m_Positions.push_back({ halfWidth, -halfHeight, -halfDepth });
		data->m_Positions.push_back({ halfWidth,  halfHeight, -halfDepth });
		data->m_Positions.push_back({ halfWidth, -halfHeight,  halfDepth });
		data->m_Positions.push_back({ halfWidth,  halfHeight,  halfDepth });
		data->m_Normals.push_back({ 1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ 1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ 1.0f, 0.0f, 0.0f });
		data->m_Normals.push_back({ 1.0f, 0.0f, 0.0f });
		data->m_Colors.push_back({ 1.0f, 0.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
		data->m_Colors.push_back({ 0.0f, 0.0f, 1.0f, 1.0f });
		data->m_Colors.push_back({ 1.0f, 1.0f, 0.0f, 1.0f });
		data->m_TexCoords.push_back({ 0.0f,  0.0f });
		data->m_TexCoords.push_back({ 0.0f,  1.0f });
		data->m_TexCoords.push_back({ 1.0f,  0.0f });
		data->m_TexCoords.push_back({ 1.0f,  1.0f });

		// 法线朝外
		data->m_Indices = { 0, 1, 2, 1, 3, 2 }; // 左面
		data->m_Indices.insert(data->m_Indices.end(), { 4, 5, 6, 5, 7, 6 }); // 后面
		data->m_Indices.insert(data->m_Indices.end(), { 8, 9, 10, 9, 11, 10 }); // 右面
		data->m_Indices.insert(data->m_Indices.end(), { 12, 13, 14, 13, 15, 14 }); // 前面
		data->m_Indices.insert(data->m_Indices.end(), { 16, 17, 18, 17, 19, 18 }); // 上面
		data->m_Indices.insert(data->m_Indices.end(), { 20, 21, 22, 21, 23, 22 }); // 下面

		return data;
	}

	void Cube::Draw()
	{
		if(HasTexture())
			m_Texture->Bind();

		m_CubeVAO->Draw();
	}
}