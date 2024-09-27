#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "sdl init video failed: " << SDL_GetError() << std::endl;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "img init failed: " << SDL_GetError() << std::endl;
	}

	SDL_Quit();
	
	return 0;
}