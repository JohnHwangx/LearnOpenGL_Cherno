#pragma once
#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererId;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void SetTextureWrap(unsigned int) const;
	void SetTextureMagFilter(unsigned int) const;
	void SetTextureMinFilter(unsigned int) const;

	void Bind(unsigned int slot = 0) const;
	void BindUnit(unsigned int slot = 0) const;
	void Unbind();

	inline unsigned int GetRendererId() const { return m_RendererId; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};