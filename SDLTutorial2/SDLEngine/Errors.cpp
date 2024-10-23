#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace SDLEngine
{
	void FatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}
}