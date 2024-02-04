#pragma once

#include "GeometryData.h"
#include <iostream>

namespace Blaze {
	class Triangle
	{
	public:
		Triangle();
		~Triangle();
		void Draw();

	private:
		GeometryData* MakeGeometryData();

	private:
		std::unique_ptr<GLStaticMesh> m_TriangleVAO;
	};
}