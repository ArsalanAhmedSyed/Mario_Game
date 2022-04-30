#include "GameScreenManager.h"
#include "GameScreen.h"
#include "SoundEffect.h"
#include "MainMenuScreen.h"
#include "ControlsScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_Current_Screen = nullptr;
	m_play_music = new SoundEffect();
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_Current_Screen;
	m_Current_Screen = nullptr;

	delete m_play_music;
	m_play_music = nullptr;
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

	MainMenuScreen* mainScreen;
	ControlsScreen* tempControlScreen;
	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen2;

	switch(new_screen)
	{
	case SCREEN_MENU:
		m_play_music->PlayMusic(MENU_MUSIC);
		mainScreen = new MainMenuScreen(m_renderer);
		m_Current_Screen = (GameScreen*)mainScreen;
		mainScreen = nullptr;

		break;
	case SCREEN_CONTROLS:
		tempControlScreen = new ControlsScreen(m_renderer);
		m_Current_Screen = (GameScreen*)tempControlScreen;
		tempControlScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_Current_Screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;

		m_play_music->PlayMusic(GAMEPLAY_MUSIC);
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(m_renderer);
		m_Current_Screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;

		m_play_music->PlayMusic(GAMEPLAY_MUSIC);
		break;
	default:
		break;
	}
}
