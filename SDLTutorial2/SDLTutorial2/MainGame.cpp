#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"

#include <iostream>
#include <string>

MainGame::MainGame()
	: _window(nullptr), _screenWidth(1024), _screenHeight(720), _gameState(GameState::PLAY), _time(0.0f)
{
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	InitSystems();

	_sprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);

	_playerTexture = ImageLoader::LoadPNG("Textures/character/idle/i1.png");

	GameLoop();
}

void MainGame::InitSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		FatalError("sdl window create error");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		FatalError("sdl glContext create error");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("glewInit error");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1);

	InitShaders();
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
		ProcessInput();
		_time += 0.01f;
		DrawGame();
	}
}

void MainGame::ProcessInput()
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << ev.motion.x << " " << ev.motion.y << std::endl;
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
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);

	_sprite.Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();

	SDL_GL_SwapWindow(_window);
}
