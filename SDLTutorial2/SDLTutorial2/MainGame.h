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

	SDLEngine::Window _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	SDLEngine::GLSLProgram _colorProgram;
	SDLEngine::Camera2D _camera2D;

	SDLEngine::SpriteBatch _spriteBatch;

	SDLEngine::InputManager _inputManager;
	SDLEngine::FPSLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _fps;
	float _maxFPS;

	float _time;
};

