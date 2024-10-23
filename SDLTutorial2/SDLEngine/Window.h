#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace SDLEngine
{
	enum WindowFlags
	{
		INVISIBLE = 1 << 0,
		FULLSCREEN = 1 << 1,
		BORDERLESS = 1 << 2
	};

	class Window
	{
	public:
		Window();
		~Window();

		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void SwapBuffer();

		int GetScreenWidth() { return _screenWidth; }
		int GetScreenHeight() { return _screenHeight; }

	private:
		SDL_Window* _window;
		int _screenWidth;
		int _screenHeight;
	};
}