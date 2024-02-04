#pragma once
#include <unordered_map>
#include "Texture.h"

namespace Blaze {
	class GLTextureCache
	{
	public:
		GLTextureCache(const GLTextureCache&) = delete;
		~GLTextureCache();

		static GLTextureCache& Get()
		{
			static GLTextureCache instance;
			return instance;
		}

		void Set(const std::string& key, const Texture& texture);
		const Texture* GetMaybe(const std::string& key);
		const Texture* GetMust(const std::string& key);
		void Remove(const std::string& key);

	private:
		GLTextureCache();

	private:
		std::unordered_map<const std::string*, const Texture*> m_Dic;
	};
}