#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Entity
{
public:
	Entity(float x, float y, SDL_Texture* tex);

	float GetX();
	float GetY();
	SDL_Rect GetCurrentFrame();
	SDL_Texture* GetTex();

private:
	float x, y;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};