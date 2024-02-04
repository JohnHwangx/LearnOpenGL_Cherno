#include "GLMeshBase.h"

namespace Blaze {

	GLMeshBase::GLMeshBase(char attribBits, char drawMode)
		:m_AttriBits(attribBits), m_Mode(drawMode)
	{
		m_AttribStride = GLAttribState::GetVertexByteStride(m_AttriBits);
		GLCall(glGenVertexArrays(1, &m_VAO));
	}

	GLMeshBase::~GLMeshBase()
	{
		GLCall(glDeleteVertexArrays(1, &m_VAO));
	}

	void GLMeshBase::Bind() const
	{
		GLCall(glBindVertexArray(m_VAO));
	}

	void GLMeshBase::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}