#include "RenderWindow.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

RenderWindow::RenderWindow(const char* title, int w, int h)
	: window(nullptr), renderer(nullptr)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Window failed to init: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

int RenderWindow::GetRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::CleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity& entity)
{
	SDL_Rect src;
	src.x = entity.GetCurrentFrame().x;
	src.y = entity.GetCurrentFrame().y;
	src.w = entity.GetCurrentFrame().w;
	src.h = entity.GetCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.GetPos().x * 4;
	dst.y = entity.GetPos().y * 4;
	dst.w = entity.GetCurrentFrame().w * 4;
	dst.h = entity.GetCurrentFrame().h * 4;

	SDL_RenderCopy(renderer, entity.GetTex(), &src, &dst);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}
