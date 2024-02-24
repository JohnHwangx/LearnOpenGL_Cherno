#pragma once
#include <iostream>
#include "Renderbuffer.h"

class GBuffer
{
public:
	GBuffer(const unsigned int width, const unsigned int height);
	~GBuffer();

	void Bind() const;
	void Unbind() const;

private:
	void BindFramebufferTexture2D(unsigned int& );
	void BindRenderbuffer();

private:

	unsigned int m_RendererID;
	unsigned int m_GPosition;
	unsigned int m_GNormal;
	unsigned int m_GAlbedoSpec;
	unsigned int m_Width, m_Height;
	unsigned int m_RboDepth;

	//std::unique_ptr<Renderbuffer> m_Renderbuffer;
};