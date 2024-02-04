#include "GLStaticMesh.h"
#include "Renderer.h"

GLStaticMesh::GLStaticMesh(char attribBits, const void* vertices, unsigned int vertexCount, const void* indices, unsigned int count, char drawMode)
	:GLMeshBase(attribBits, drawMode),m_VertCount(vertexCount), m_IndexCount(count)
{
	unsigned int vbSize = GLAttribState::GetVertexBufferSize(attribBits, vertexCount);

	Bind();
	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));//…Ë÷√◊¥Ã¨
	GLCall(glBufferData(GL_ARRAY_BUFFER, vbSize * sizeof(float), vertices, GL_STATIC_DRAW));

	GLAttribOffsetMap offsetMap = GLAttribState::GetInterleavedLayoutAttribOffsetMap(attribBits);
	GLAttribState::SetAttribVertexArrayPointer(offsetMap);
	GLAttribState::SetAttribVertexArrayState(m_AttriBits);

	SetIBO(indices, count);
}

GLStaticMesh::~GLStaticMesh()
{
}

void GLStaticMesh::Draw()
{
	Bind();
	if (m_IBO)
	{
		GLCall(glDrawElements(m_Mode, m_IndexCount, GL_UNSIGNED_INT, 0));
	}
	else
	{
		GLCall(glDrawArrays(m_Mode, 0, m_VertCount));
	}
}

void GLStaticMesh::SetIBO(const void* indices, unsigned int count)
{
	if (count == 0)
		return;

	GLCall(glGenBuffers(1, &m_IBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

