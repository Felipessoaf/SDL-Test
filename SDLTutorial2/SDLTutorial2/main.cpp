#include <Windows.h>
#include <GL/glew.h>

//#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
//
#include <iostream>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame mainGame;
	mainGame.Run();
	
	return 0;
}