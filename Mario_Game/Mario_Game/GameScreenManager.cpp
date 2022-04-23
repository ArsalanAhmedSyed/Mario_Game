#include "GameScreenManager.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_Renderer = renderer;
	m_Current_Screen = nullptr;

	ChangeScreen(startScreen);
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
	GameScreenLevel2* tempScreen2;

	switch(new_screen)
	{
	case SCREEN_MENU:
		mainScreen = new MainMenuScreen(m_Renderer);
		m_Current_Screen = (GameScreen*)mainScreen;
		mainScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_Renderer);
		m_Current_Screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(m_Renderer);
		m_Current_Screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;
	default:
		break;
	}
}
