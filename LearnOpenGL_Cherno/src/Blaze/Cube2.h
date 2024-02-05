#pragma once
#include <iostream>
#include "Geometry.h"
//#include "GeometryData.h"

namespace Blaze {

	class Cube: public Geometry
	{
	public:
		Cube(const float width = 0.4f, const float height = 0.4f, const float depth = 0.4f, const Texture* texture = nullptr);
		~Cube();

		void Draw();

	protected:
		GeometryData* MakeGeometryData() override;

	private:
		float m_Width, m_Height, m_Depth;

		std::unique_ptr<GLStaticMesh> m_CubeVAO;
	};
}