#pragma once

class Framebuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_TextureID;

	unsigned int m_Width, m_Height;

public:
	Framebuffer(const unsigned int width,const unsigned int height);
	~Framebuffer();
	void Bind() const;
	void Unbind() const;

	inline const unsigned int GetTextureId() const { return m_TextureID; }
};