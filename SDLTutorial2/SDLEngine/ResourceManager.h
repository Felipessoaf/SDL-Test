#pragma once

#include "TextureCache.h"

namespace SDLEngine
{
	class ResourceManager
	{
	public:
		static GLTexture GetTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};
}