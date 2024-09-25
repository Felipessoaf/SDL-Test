#include "RenderWindow.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

RenderWindow::RenderWindow(const char* title, int w, int h)
	: window(nullptr), renderer(nullptr)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Window failed to init: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::CleanUp()
{
	SDL_DestroyWindow(window);
}
