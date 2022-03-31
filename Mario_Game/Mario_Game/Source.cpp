//SDL liberaies
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//C++ liberaies
#include <iostream>

//Header files
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std;

//functions
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

//Audio
void LoadMusic();
Mix_Music* g_music = nullptr;	

SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;


//Initialise SDL
bool InitSDL()
{
	bool success = true;
	
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. Error: %s\n" << SDL_GetError();
		success = false;
	}
	else
	{
		//Create Window
		g_Window = SDL_CreateWindow("Mario Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_Window == nullptr)
		{
			cout << "Window was not created. Error: %s\n" << SDL_GetError();
			success = false;
		}
		
		//Create Renderer
		g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
		if (g_Renderer == nullptr)
		{
			cout << "Renderer was not created. Error: %s\n" << SDL_GetError();
			success = false;
		}
		else
		{
			//Initalise SDL image
			int imageFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlag) & imageFlag))
			{
				cout << "SDL_Image could not be initialise. IMG_ERROR: %s" << IMG_GetError();
				success = false;
			}
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000) < 0)
		{
			cout << "Mixer could not initialise! Error: " << Mix_GetError();
			success = false;
		}
	}
	return success;
}

void LoadMusic()
{
	g_music = Mix_LoadMUS("Audio/Mario.mp3");
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: %s " << Mix_GetError() << endl;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(g_music, -1);
	}
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_Renderer);
	//Setup Image Render format
	game_screen_manager->Render();

	//Update the screen
	SDL_RenderPresent(g_Renderer);
}

//event check
bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

//close everything
void CloseSDL()
{
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//Release the renderer
	SDL_DestroyRenderer(g_Renderer);
	g_Renderer = nullptr;

	//Deletes window
	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	//release the audio
	Mix_FreeMusic(g_music);
	g_music = nullptr;

	//Quit SDL_Image
	IMG_Quit();
	//Quit SDL
	SDL_Quit();
	//Quit Mixer
	Mix_Quit();
	
}

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//LoadMusic();
		
		game_screen_manager = new GameScreenManager(g_Renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}	
	}
	
	CloseSDL();
	return 0;
}

