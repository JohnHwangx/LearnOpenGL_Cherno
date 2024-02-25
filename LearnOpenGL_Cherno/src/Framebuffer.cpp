#include "Framebuffer.h"

#include "Renderer.h"
#include <iostream>

Framebuffer::Framebuffer()
    :m_Width(0), m_Height(0)
{
    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

Framebuffer::Framebuffer(const unsigned int width, const unsigned int height)
    :m_Width(width), m_Height(height)
{

    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

    // create a color attachment texture
    m_Texture = std::make_unique<Texture>();
    m_Texture->BindEmpth(m_Width, m_Height);
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->GetRendererId(), 0));
    //GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Texture->GetRendererId(), 0));

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    m_Renderbuffer = std::make_unique<Renderbuffer>(m_Width, m_Height);
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer->GetRendererId())); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

Framebuffer::~Framebuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
}

void Framebuffer::MakeDepthFramebuffer(const unsigned int width, const unsigned int height)
{
    m_Width = width;
    m_Height = height;

    // create a color attachment texture
    m_Texture = std::make_unique<Texture>();
    m_Texture->BindDepth(m_Width, m_Height);
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Texture->GetRendererId(), 0));
    GLCall(glDrawBuffer(GL_NONE));
    GLCall(glReadBuffer(GL_NONE));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Framebuffer::BindTexture(unsigned int slot)
{
    m_Texture->Bind(slot);
}

void Framebuffer::Bind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void Framebuffer::Unbind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
