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
void UpdateMusic();

Mix_Music* g_music = nullptr;	
Mix_Music* g_menuMusic = nullptr;

SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
GameScreenManager* game_screen_manager = nullptr;
Uint32 g_old_time;

//veraible
MUSIC m_music;
bool changeMusic = false;
bool MenuScreen = false;
bool GameScreen = true;

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
	g_music = Mix_LoadMUS("Audio/MarioMusic.wav");
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: %s " << Mix_GetError() << endl;
	}

	g_menuMusic = Mix_LoadMUS("Audio/MainMenuTheme.wav");
	if (g_menuMusic == nullptr)
	{
		cout << "Failed to load Menu music. Error: %s " << Mix_GetError() << endl;
	}
}

void UpdateMusic()
{
	if (m_music == GAMEPLAY_MUSIC)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
	}
	else if (m_music == MENU_MUSIC)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_menuMusic, -1);
		}
	}

	if (changeMusic)
	{
		changeMusic = false;

		if (Mix_PlayingMusic() == 1)
		{
			Mix_HaltMusic();
		}
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
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			if (!MenuScreen)
			{
			case SDLK_ESCAPE:
				if (MenuScreen)
				{
					game_screen_manager->ChangeScreen(SCREEN_MENU);

					GameScreen = true;
					MenuScreen = false;
					changeMusic = true;

					m_music = MENU_MUSIC;
				}
				break;
			}
		case SDLK_0:
				game_screen_manager->ChangeScreen(SCREEN_INTRO);
			break;
		case SDLK_1:
			if (GameScreen)
			{
				game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
				changeMusic = true;
				GameScreen = false;
				MenuScreen = true;

				m_music = GAMEPLAY_MUSIC;
			}
			break;
		case SDLK_2:
			if (GameScreen)
			{
				game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
				changeMusic = true;
				MenuScreen = true;
				GameScreen = false;

				m_music = GAMEPLAY_MUSIC;
			}
			break;
		}
		break;
	}

	UpdateMusic();

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

	Mix_FreeMusic(g_menuMusic);
	g_menuMusic = nullptr;

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
		LoadMusic();

		game_screen_manager = new GameScreenManager(g_Renderer, SCREEN_MENU);

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

