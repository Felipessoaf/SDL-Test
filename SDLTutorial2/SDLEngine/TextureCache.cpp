#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace SDLEngine
{
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::GetTexture(std::string texturePath)
	{
		auto mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::LoadPNG(texturePath);
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "loaded and cached texture" << std::endl;

			return newTexture;
		}

		std::cout << "used already cached texture" << std::endl;

		return mit->second;
	}
}