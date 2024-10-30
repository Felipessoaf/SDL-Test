#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <vector>

#include <SDLEngine/GLSLProgram.h>
#include <SDLEngine/Sprite.h>		 
#include <SDLEngine/GLTexture.h>
#include <SDLEngine/Window.h>
#include <SDLEngine/Camera2D.h>
#include <SDLEngine/SpriteBatch.h>
#include <SDLEngine/InputManager.h>
#include <SDLEngine/Timing.h>

#include "Bullet.h"

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

private:
	void InitSystems();
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();

	SDLEngine::Window m_window;
	int m_screenWidth;
	int m_screenHeight;

	GameState m_gameState;

	SDLEngine::GLSLProgram m_colorProgram;
	SDLEngine::Camera2D m_camera2D;

	SDLEngine::SpriteBatch m_spriteBatch;

	SDLEngine::InputManager m_inputManager;
	SDLEngine::FPSLimiter m_fpsLimiter;

	std::vector<Bullet> _bullets;

	float m_fps;
	float m_maxFPS;

	float m_time;
};

