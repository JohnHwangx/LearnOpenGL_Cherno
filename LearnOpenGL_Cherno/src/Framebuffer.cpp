#include "Framebuffer.h"

#include "Renderer.h"

Framebuffer::Framebuffer(const unsigned int* data, unsigned int count)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::Bind() const
{
}

void Framebuffer::Unbind() const
{
}
