#include "Entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* tex)
	: pos(pos), tex(tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

SDL_Rect Entity::GetCurrentFrame()
{
	return currentFrame;
}

SDL_Texture* Entity::GetTex()
{
	return tex;
}
