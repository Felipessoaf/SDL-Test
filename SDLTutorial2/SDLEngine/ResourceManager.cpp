#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
	return _textureCache.GetTexture(texturePath);
}
