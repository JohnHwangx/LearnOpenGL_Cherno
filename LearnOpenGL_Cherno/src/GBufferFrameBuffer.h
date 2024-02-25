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

	void ActiveTextures();

	inline unsigned int GetRendererID() const { return m_RendererID; }
	inline unsigned int GetGPositionTexture() const { return m_GPosition; }
	inline unsigned int GetGNormalTexture() const { return m_GNormal; }
	inline unsigned int GetGAlbedoSpecTexture() const { return m_GAlbedoSpec; }

private:
	void BindFramebufferTexture2D(unsigned int&, unsigned int slot = 0);
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