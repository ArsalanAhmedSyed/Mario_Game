#include "GameScreenManager.h"
#include "MainMenueScreen.h"
#include "SoundEffect.h"
#include "Texture2D.h"

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupMenu();
}

MainMenuScreen::~MainMenuScreen()
{
	delete m_menuBackground_texture;
	m_menuBackground_texture = nullptr;

	delete m_music;
	m_music = nullptr;
}

void MainMenuScreen::Render()
{
	m_menuBackground_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
}

void MainMenuScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_0:
			m_gameManger_screen->ChangeScreen(SCREEN_INTRO);
			break;
		case SDLK_1:
			m_gameManger_screen->ChangeScreen(SCREEN_LEVEL1);
			break;
	/*	case SDLK_2:
			m_gameManger_screen->ChangeScreen(SCREEN_LEVEL2);
			break;*/
		default:
			m_gameManger_screen->ChangeScreen(SCREEN_MENU);
		}
		break;
	}
}

bool MainMenuScreen::SetupMenu()
{
	bool success = true;

	m_menuBackground_texture = new Texture2D(m_Renderer);
	if (!m_menuBackground_texture->LoadFromFile("Images/MainMenu.png"))
	{
		cout << "Could not load background!" << endl;
		success = false;
	}

	m_music = new SoundEffect();
	m_gameManger_screen = new GameScreenManager(m_Renderer,SCREEN_MENU);

	return success;
}