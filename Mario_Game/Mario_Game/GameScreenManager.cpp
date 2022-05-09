#include "GameScreenManager.h"
#include "GameScreen.h"
#include "SoundEffect.h"
#include "SelectionScreen.h"
#include "MainMenuScreen.h"
#include "ControlsScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	m_gameplay = false;

	//Initalize soundeffect file
	m_play_music = new SoundEffect();
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	//call gamescreen file deconstructor
	delete m_current_screen;
	m_current_screen = nullptr;

	//call soundeffect decontructor 
	delete m_play_music;
	m_play_music = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltatime, SDL_Event e)
{
	m_current_screen->Update(deltatime, e);

	//Check if character is selcected
	if (m_current_screen->GetSelection() == true)
	{
		//Get the selected character
		selectedCharacter = m_current_screen->SelectedCharacter();
		ChangeScreen(SCREEN_MENU);
		m_current_screen->SetSelection(false);
		m_gameplay = true;
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (!m_gameplay)
			{
				//Load menu screen
				ChangeScreen(SCREEN_MENU);
				m_gameplay = true;
			}
			break;
		case SDLK_0:
			if (m_gameplay)
			{
				//Load Controls screen
				ChangeScreen(SCREEN_CONTROLS);
				m_gameplay = false;
			}
			break;
		case SDLK_1:
			if (m_gameplay)
			{
				//Load Level 1 screen
				ChangeScreen(SCREEN_LEVEL1);
				m_gameplay = false;
				break;
			}
		case SDLK_2:
			if (m_gameplay)
			{
				//Load Level 2 screen
				ChangeScreen(SCREEN_LEVEL2);
				m_gameplay = false;
			}
			break;
		}
		break;
	}
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//Delete any exisiting screen insidee this game screen class
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	//Temporary Call out for each screen
	SelectionScreen* selectionScreen;
	MainMenuScreen* mainScreen;
	ControlsScreen* tempControlScreen;
	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen2;

	//set m_current_screen to the Enum name being passed in 
	switch(new_screen)
	{
	case SCREEN_SELECTION:
		selectionScreen = new SelectionScreen(m_renderer);
		m_current_screen = (GameScreen*)selectionScreen;
		selectionScreen = nullptr;
		break;
	case SCREEN_MENU:
		mainScreen = new MainMenuScreen(m_renderer);
		m_current_screen = (GameScreen*)mainScreen;
		mainScreen = nullptr;
		m_play_music->PlayMusic(MENU_MUSIC);
		break;
	case SCREEN_CONTROLS:
		tempControlScreen = new ControlsScreen(m_renderer);
		m_current_screen = (GameScreen*)tempControlScreen;
		tempControlScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer, selectedCharacter);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		m_play_music->PlayMusic(GAMEPLAY_MUSIC);
		break;
	case SCREEN_LEVEL2:
		/*tempScreen2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;*/
		m_play_music->PlayMusic(GAMEPLAY_MUSIC);
		break;
	default:
		break;
	}
}
