#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* LoadTexture(const char* filePath);
	void CleanUp();
	void Clear();
	void Render(SDL_Texture* tex);
	void Display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};