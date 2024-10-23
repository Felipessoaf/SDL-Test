#pragma once

#include "TextureCache.h"

class ResourceManager
{
public:
	static GLTexture GetTexture(std::string texturePath);

private:
	static TextureCache _textureCache;
};

