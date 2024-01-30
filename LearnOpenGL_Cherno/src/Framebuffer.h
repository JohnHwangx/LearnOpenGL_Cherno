#pragma once
#include <iostream>
#include "Texture.h"
#include "Renderbuffer.h"

class Framebuffer
{
public:
	Framebuffer();
	Framebuffer(const unsigned int width,const unsigned int height);
	~Framebuffer();
	void Bind() const;
	void Unbind() const;

	void MakeDepthFramebuffer(const unsigned int width, const unsigned int height);

	inline Texture* GetTexture() { return m_Texture.get(); }

private:
	unsigned int m_RendererID;
	unsigned int m_Width, m_Height;

	std::unique_ptr<Texture> m_Texture;
	std::unique_ptr<Renderbuffer> m_Renderbuffer;
};