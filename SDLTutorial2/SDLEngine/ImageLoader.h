#pragma once

#include "GLTexture.h"
#include <string>

namespace SDLEngine
{
	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(std::string filePath);
	};
}

