#include "Errors.h"

#include <iostream>
#include <SDL/SDL.h>

void FatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}