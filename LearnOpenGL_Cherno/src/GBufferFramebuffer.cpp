#include "GBufferFrameBuffer.h"

GBuffer::GBuffer(const unsigned int width, const unsigned int height)
	:m_Width(width), m_Height(height)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	BindFramebufferTexture2D(m_GPosition);
	BindFramebufferTexture2D(m_GNormal, 1);
	BindFramebufferTexture2D(m_GAlbedoSpec, 2);

	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	GLCall(glDrawBuffers(3, attachments));

	BindRenderbuffer();

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GBuffer::~GBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
}

void GBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void GBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void GBuffer::ActiveTextures()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_GPosition));
	GLCall(glActiveTexture(GL_TEXTURE1));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_GNormal));
	GLCall(glActiveTexture(GL_TEXTURE2));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_GAlbedoSpec));
}

void GBuffer::BindFramebufferTexture2D(unsigned int& rendererID, unsigned int slot)
{
	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, rendererID, 0));
}

void GBuffer::BindRenderbuffer()
{
	GLCall(glGenRenderbuffers(1, &m_RboDepth));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RboDepth));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RboDepth));
}
