#pragma once
#include <unordered_map>
#include "Texture.h"

namespace Blaze {
	class GLTextureCache
	{
	public:
		~GLTextureCache();

	private:
		GLTextureCache() {};

	private:
		std::unordered_map<const std::string&, const Texture&> m_Idc;
	};
}