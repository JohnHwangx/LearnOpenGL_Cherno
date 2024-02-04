#pragma once
#include "GLAttribState.h"
#include "Renderer.h"

namespace Blaze {
	class GLMeshBase
	{
	public:
		GLMeshBase(char attribBits, char drawMode = GL_TRIANGLES);
		~GLMeshBase();

		void Bind() const;
		void Unbind() const;

		inline char GetVertexStride() const { return m_AttribStride; }

	protected:
		unsigned int m_VAO;
		char m_Mode;
		char m_AttriBits;
		char m_AttribStride;
	};
}