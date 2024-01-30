#include "Renderbuffer.h"

Renderbuffer::Renderbuffer(const unsigned int width, const unsigned int height)
{
    GLCall(glGenRenderbuffers(1, &m_RendererId));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererId));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, width)); // use a single renderbuffer object for both a depth AND stencil buffer.
}

Renderbuffer::~Renderbuffer()
{
}
