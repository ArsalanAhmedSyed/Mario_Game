#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "MainMenuScreen.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_Renderer = renderer;
	m_Current_Screen = nullptr;

	ChangeScreen(startScreen);

	m_play_Menu_Music = false;
}

GameScreenManager::~GameScreenManager()
{
	m_Renderer = nullptr;

	delete m_Current_Screen;
	m_Current_Screen = nullptr;
}

void GameScreenManager::Render()
{
	m_Current_Screen->Render();
}

void GameScreenManager::Update(float deltatime, SDL_Event e)
{
	m_Current_Screen->Update(deltatime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_Current_Screen != nullptr)
	{
		delete m_Current_Screen;
	}

	GameScreenLevel1* tempScreen;
	MainMenuScreen* mainScreen;

	switch(new_screen)
	{
	case SCREEN_MENU:
		mainScreen = new MainMenuScreen(m_Renderer);
		m_Current_Screen = (GameScreen*)mainScreen;
		mainScreen = nullptr;
		m_play_Menu_Music = true;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_Renderer);
		m_Current_Screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		m_play_Menu_Music = false;
		break;
	default:
		break;
	}
}
