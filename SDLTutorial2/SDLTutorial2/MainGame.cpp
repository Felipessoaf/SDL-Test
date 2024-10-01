#include "MainGame.h"

#include <iostream>
#include <string>

void FatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

MainGame::MainGame()
	: _screenWidth(1024), _screenHeight(720), _gameState(GameState::PLAY)
{
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
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		ProcessInput();
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

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);

	glEnd();

	SDL_GL_SwapWindow(_window);
}
