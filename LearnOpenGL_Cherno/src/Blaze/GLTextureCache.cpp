#include "GLTextureCache.h"

namespace Blaze {

	GLTextureCache::GLTextureCache()
	{

	}

	GLTextureCache::~GLTextureCache()
	{
	}

	void GLTextureCache::Set(const std::string& key, const Texture& texture)
	{
		m_Dic.insert(std::pair<const std::string*, const Texture*>(&key, &texture));
	}

	const Texture* GLTextureCache::GetMaybe(const std::string& key)
	{
		return m_Dic.at(&key);
	}

	const Texture* GLTextureCache::GetMust(const std::string& key)
	{
		if (m_Dic.find(&key) == m_Dic.end())
			throw;

		return m_Dic.at(&key);
	}

	void GLTextureCache::Remove(const std::string& key)
	{
	}
}