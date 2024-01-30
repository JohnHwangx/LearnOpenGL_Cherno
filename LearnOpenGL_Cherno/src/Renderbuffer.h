#pragma once
#include "Renderer.h"

class Renderbuffer
{
public:
	Renderbuffer(const unsigned int width, const unsigned int height);
	~Renderbuffer();

	inline unsigned int GetRendererId() const { return m_RendererId; }
private:
	unsigned int m_RendererId;
};