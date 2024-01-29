#pragma once

class Framebuffer
{
private:
	unsigned int m_RendererID;
public:
	Framebuffer(const unsigned int* data, unsigned int count);
	~Framebuffer();
	void Bind() const;
	void Unbind() const;
};