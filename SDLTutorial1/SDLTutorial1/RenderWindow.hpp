#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* title, int w, int h);
	void CleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};