#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

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

	SDL_Texture* grassTexture = window.LoadTexture("../res/gfx/ground_grass_1.png");

	Entity platform0(50, 50, grassTexture);

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

		window.Clear();
		window.Render(platform0);
		window.Display();
	}

	window.CleanUp();
	SDL_Quit();
	
	return 0;
}