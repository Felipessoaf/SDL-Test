#include "Window.h"
#include "Errors.h"
#include "Vertex.h"

namespace SDLEngine
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags, const Color& backgroundColor)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

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

		std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		//background color
		glClearColor(backgroundColor.r / 255.0f, backgroundColor.g / 255.0f, backgroundColor.b / 255.0f, backgroundColor.a / 255.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);

		//enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(_window);
	}
}