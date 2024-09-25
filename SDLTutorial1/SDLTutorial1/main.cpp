#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"

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

	std::vector<Entity> entities = {
		Entity (Vector2f(0, 0), grassTexture),
		Entity (Vector2f(30, 0), grassTexture),
		Entity (Vector2f(30, 30), grassTexture)
	};
	

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

		for (Entity& entity : entities)
		{
			window.Render(entity);
		}

		window.Display();
	}

	window.CleanUp();
	SDL_Quit();
	
	return 0;
}