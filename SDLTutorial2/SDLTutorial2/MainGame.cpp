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
		float startTicks = SDL_GetTicks();

		ProcessInput();
		_time += 0.01f;

		_camera2D.Update();

		DrawGame();
		CalculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event ev;

	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << ev.motion.x << " " << ev.motion.y << std::endl;
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym)
				{
					case SDLK_w:
						_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
						break;
					case SDLK_s:
						_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
						break;
					case SDLK_a:
						_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
						break;
					case SDLK_d:
						_camera2D.SetPosition(_camera2D.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
						break;
					case SDLK_q:
						_camera2D.SetScale(_camera2D.GetScale() + SCALE_SPEED);
						break;
					case SDLK_e:
						_camera2D.SetScale(_camera2D.GetScale() - SCALE_SPEED);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
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

	GLint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);

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

	for (int i = 0; i < 1000; i++)
	{
		_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);
		_spriteBatch.Draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	}

	_spriteBatch.End();
	_spriteBatch.RenderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();

	_window.SwapBuffer();
}

void MainGame::CalculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	previousTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
}
