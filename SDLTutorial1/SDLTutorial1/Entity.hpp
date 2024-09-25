#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f pos, SDL_Texture* tex);

	Vector2f& GetPos()
	{
		return pos;
	}

	SDL_Rect GetCurrentFrame();
	SDL_Texture* GetTex();

private:
	Vector2f pos;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};