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

SDL_Texture* RenderWindow::LoadTexture(const char* filePath)
{
	SDL_Texture* texture = nullptr;

	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == nullptr)
	{
		std::cout << "texture load failed to init: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::CleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(SDL_Texture* tex)
{
	SDL_RenderCopy(renderer, tex, nullptr, nullptr);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}
