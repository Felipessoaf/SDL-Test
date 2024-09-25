#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

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

	RenderWindow window("Game v1.0", 1280, 720);

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}
	}

	window.CleanUp();
	SDL_Quit();
	
	return 0;
}