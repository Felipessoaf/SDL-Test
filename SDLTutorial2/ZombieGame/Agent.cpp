#include "Agent.h"

#include <SDLEngine/GLTexture.h>
#include <SDLEngine/ResourceManager.h>

Agent::Agent(glm::vec2 direction, glm::vec2 position, float speed, std::string texturePath) :
	m_direction(direction),
	m_position(position),
	m_speed(speed)
{
	m_texture = SDLEngine::ResourceManager::GetTexture(texturePath);
}

Agent::~Agent()
{
}

void Agent::Draw(SDLEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	SDLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, 30, 30);

	spriteBatch.Draw(posAndSize, uv, m_texture.id, 0.0f, color);
}

void Agent::Update()
{
	m_position += m_direction * m_speed;

	// Check for collision and adjust position
}