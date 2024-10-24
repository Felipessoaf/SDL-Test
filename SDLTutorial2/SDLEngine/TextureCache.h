#pragma once

#include <map>
#include <string>
#include "GLTexture.h"

namespace SDLEngine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture GetTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}