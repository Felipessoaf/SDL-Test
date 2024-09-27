#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

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
	void GameLoop();
	void ProcessInput();

	SDL_Window* _window = nullptr;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
};
