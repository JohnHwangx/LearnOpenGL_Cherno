#pragma once
#include <iostream>
#include "Texture.h"

class Framebuffer
{
public:
	Framebuffer(const unsigned int width,const unsigned int height);
	~Framebuffer();
	void Bind() const;
	void Unbind() const;

	inline Texture* GetTexture() { return m_Texture.get(); }

private:
	unsigned int m_RendererID;
	unsigned int m_Width, m_Height;

	std::unique_ptr<Texture> m_Texture;
};