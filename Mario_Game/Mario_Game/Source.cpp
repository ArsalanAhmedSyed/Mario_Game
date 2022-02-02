//SDL liberaies
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//C++ liberaies
#include <iostream>

//Header files
#include "constants.h"

using namespace std;

//functions
bool InitSDL();
void CloseSDL();
bool Update();

SDL_Window* g_window = nullptr;

//Initialise SDL
bool InitSDL()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		success = false;
	}
	else
	{
		g_window = SDL_CreateWindow("Mario Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == nullptr)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			success = false;
		}
	}
	return success;
}

//close everything
void CloseSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

//event check
bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch(e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	return false;
}

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		while (!quit)
		{
			quit = Update();
		}
	}
	
	CloseSDL();
	return 0;
}

