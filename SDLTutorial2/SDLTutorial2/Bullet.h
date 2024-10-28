#pragma once

#include <glm/glm.hpp>
#include <SDLEngine/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 direction, glm::vec2 position, float speed, int lifeTime);
	~Bullet();

	void Draw(SDLEngine::SpriteBatch& spriteBatch);
	bool Update();

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};

