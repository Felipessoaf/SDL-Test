#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Entity;

class RenderWindow
{
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* LoadTexture(const char* filePath);

	int GetRefreshRate();

	void CleanUp();
	void Clear();
	void Render(Entity& entity);
	void Display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};