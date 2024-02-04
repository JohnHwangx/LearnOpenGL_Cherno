#pragma once
#include "GLMeshBase.h"

namespace Blaze {
	class GLStaticMesh : public GLMeshBase
	{
	public:
		GLStaticMesh(char attribBits, const void* vertices, unsigned int vertexSize, const void* indices, unsigned int count, char drawMode = GL_TRIANGLES);
		~GLStaticMesh();

		void Draw();
	protected:
		void SetIBO(const void* indices, unsigned int count);
	protected:
		unsigned int m_VBO;
		unsigned int m_IBO;

		unsigned int m_VertCount;
		unsigned int m_IndexCount;
	};
}