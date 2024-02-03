#pragma once
#include "GLStaticMesh.h"

namespace Blaze {
	struct Vec2
	{
		float x, y;
	};
	struct Vec3
	{
		float x, y, z;
	};
	struct Vec4
	{
		union
		{
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				float x, y, z, w;
			};
		};
	};

	struct Vertex
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;
		Vec4 Color;
		Vec4 Tangent;
	};

	class GeometryData
	{
	public:
		GeometryData();
		~GeometryData();

		GLStaticMesh* MakeStaticVAO(bool needNormals = false, bool needUvs = true);
		char GetAttribBits();
	public:
		//Vertex* m_Vertices;
		std::vector<Vec3> m_Positions;
		std::vector<Vec3> m_Normals;
		std::vector<Vec2> m_TexCoords;
		std::vector<Vec4> m_Colors;
		std::vector<Vec4> m_Tangents;
		std::vector<unsigned int> m_Indices;
	};
}