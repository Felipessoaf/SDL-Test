#pragma once

#include <glm/glm.hpp>

#include <SDLEngine/SpriteBatch.h>
#include <SDLEngine/GLTexture.h>

#include <string>

class Agent
{
public:
	Agent(glm::vec2 position, float speed, std::string texturePath);
	~Agent();

	void Draw(SDLEngine::SpriteBatch& spriteBatch);
	void Update();

	virtual void UpdateDirection() = 0;

	bool GetIsAlive() const { return m_isAlive; }

private:
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;

	SDLEngine::GLTexture m_texture;

	bool m_isAlive{ true };
};