#include "GeometryData.h"

namespace Blaze {
	GeometryData::GeometryData()
	{
	}

	GeometryData::~GeometryData()
	{
	}

	GLStaticMesh* GeometryData::MakeStaticVAO(bool needNormals, bool needUvs)
	{
		char bits = GetAttribBits();
		if (needNormals == false)
			bits &= ~GLAttribState::NORMAL_BIT;
		if (needUvs == false)
			bits &= ~GLAttribState::TEXCOORD_BIT;

		unsigned int stride = GLAttribState::GetVertexByteStride(bits);
		unsigned int step = stride / GLAttribState::FLOAT32_SIZE;

		unsigned int vertexCount = m_Positions.size();
		const unsigned int bufferLength = stride * vertexCount;
		float* buffer = new float[bufferLength]();
		for (size_t i = 0; i < vertexCount; i++)
		{
			unsigned int j = i * step;
			unsigned int idx = 0;
			buffer[j + (idx++)] = m_Positions[i].x;
			buffer[j + (idx++)] = m_Positions[i].y;
			buffer[j + (idx++)] = m_Positions[i].z;

			if (bits & GLAttribState::NORMAL_BIT)
			{
				buffer[j + (idx++)] = m_Normals[i].x;
				buffer[j + (idx++)] = m_Normals[i].y;
				buffer[j + (idx++)] = m_Normals[i].z;
			}
			if (bits & GLAttribState::TEXCOORD_BIT)
			{
				buffer[j + (idx++)] = m_TexCoords[i].x;
				buffer[j + (idx++)] = m_TexCoords[i].y;
			}
			if (bits & GLAttribState::COLOR_BIT)
			{
				buffer[j + (idx++)] = m_Colors[i].r;
				buffer[j + (idx++)] = m_Colors[i].g;
				buffer[j + (idx++)] = m_Colors[i].b;
				buffer[j + (idx++)] = m_Colors[i].a;
			}
			if (bits & GLAttribState::TANGENT_BIT)
			{
				buffer[j + (idx++)] = m_Tangents[i].x;
				buffer[j + (idx++)] = m_Tangents[i].y;
				buffer[j + (idx++)] = m_Tangents[i].z;
				buffer[j + (idx++)] = m_Tangents[i].w;
			}
		}

		unsigned int indexCount = m_Indices.size();
		unsigned int* indices = new unsigned int[indexCount];
		for (size_t i = 0; i < indexCount; i++)
		{
			indices[i] = m_Indices[i];
		}

		GLStaticMesh* mesh = new GLStaticMesh(bits, buffer, vertexCount, indices, indexCount);

		return mesh;
	}

	char GeometryData::GetAttribBits()
	{
		if (m_Positions.size() == 0)
			throw;

		char bits = GLAttribState::POSITION_BIT;
		if (m_TexCoords.size() > 0)
			bits |= GLAttribState::TEXCOORD_BIT;
		if (m_Normals.size() > 0)
			bits |= GLAttribState::NORMAL_BIT;
		if (m_Colors.size() > 0)
			bits |= GLAttribState::COLOR_BIT;
		if (m_Tangents.size() > 0)
			bits |= GLAttribState::TANGENT_BIT;

		return bits;
	}

}