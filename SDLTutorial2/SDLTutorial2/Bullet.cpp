#include "Bullet.h"

#include <SDLEngine/GLTexture.h>
#include <SDLEngine/ResourceManager.h>

Bullet::Bullet(glm::vec2 direction, glm::vec2 position, float speed, int lifeTime) :
	_lifeTime(lifeTime),
	_direction(direction),
	_position(position),
	_speed(speed)
{
}

Bullet::~Bullet()
{
}

void Bullet::Draw(SDLEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static SDLEngine::GLTexture texture = SDLEngine::ResourceManager::GetTexture("Textures/character/idle/i1.png");

	SDLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.Draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::Update()
{
	_position += _direction * _speed;
	_lifeTime--;

	if (_lifeTime == 0)
	{
		return true;
	}

	return false;
}
