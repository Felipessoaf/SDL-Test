#include "MainGame.h"

#include <SDLEngine/Errors.h>
#include <SDLEngine/SDLEngine.h>
#include <SDLEngine/ResourceManager.h>

#include <iostream>
#include <string>

MainGame::MainGame() :
	_screenWidth(1024), 
	_screenHeight(720), 
	_gameState(GameState::PLAY), 
	_time(0.0f),
	_maxFPS(60.0f)
{
	_camera2D.Init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	InitSystems();

	GameLoop();
}

void MainGame::InitSystems()
{
	SDLEngine::init();

	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);

	InitShaders();

	_spriteBatch.Init();
	_fpsLimiter.Init(_maxFPS);
}

void MainGame::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/ColorShading.vert", "Shaders/ColorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.AddAttribute("vertexUV");
	_colorProgram.LinkShaders();
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.Begin();

		ProcessInput();
		_time += 0.01f;

		_camera2D.Update();

		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].Update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}

		DrawGame();

		_fps = _fpsLimiter.End();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10000)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event ev;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.SetMouseCoords(ev.motion.x, ev.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.PressKey(ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.ReleaseKey(ev.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.PressKey(ev.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.ReleaseKey(ev.button.button);
				break;
			default:
				break;
		}
	}

	if (_inputManager.IsKeyPressed(SDLK_w))
	{
		_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
		
	if (_inputManager.IsKeyPressed(SDLK_s))
	{
		_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
		
	if (_inputManager.IsKeyPressed(SDLK_a))
	{
		_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
		
	if (_inputManager.IsKeyPressed(SDLK_d))
	{
		_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
		
	if (_inputManager.IsKeyPressed(SDLK_q))
	{
		_camera2D.SetScale(_camera2D.GetScale() + SCALE_SPEED);
	}
		
	if (_inputManager.IsKeyPressed(SDLK_e))
	{
		_camera2D.SetScale(_camera2D.GetScale() - SCALE_SPEED);
	}

	if (_inputManager.IsKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.GetMouseCoords();
		mouseCoords = _camera2D.ConvertScreenToWorld(mouseCoords);
		
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(mouseCoords, direction, 0.01f, 1000);
	}		
}

void MainGame::DrawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = _colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.Begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static SDLEngine::GLTexture texture = SDLEngine::ResourceManager::GetTexture("Textures/character/idle/i1.png");
	SDLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Draw(_spriteBatch);
	}

	_spriteBatch.End();
	_spriteBatch.RenderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();

	_window.SwapBuffer();
}
