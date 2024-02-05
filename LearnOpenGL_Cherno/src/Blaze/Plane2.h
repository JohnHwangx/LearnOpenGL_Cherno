#pragma once

#include <iostream>
#include "Geometry.h"

namespace Blaze {

	class Plane : public Geometry
	{
	public:
		Plane(float width = 10.0f, float height = 10.0f, const Texture* texture = nullptr);
		~Plane();

		void Draw();

	private:
		GeometryData* MakeGeometryData();

	private:
		float m_Width, m_Height;

		std::unique_ptr<GLStaticMesh> m_PlaneVAO;
	};
}