#pragma once
#include "GeometryData.h"

namespace Blaze {
	class Cube2
	{
	public:
		Cube2(float width = 0.4f, float height = 0.4f, float depth = 0.4f);
		~Cube2();

		GeometryData* MakeGeometryData();
	private:
		float m_Width, m_Height, m_Depth;
	};
}