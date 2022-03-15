#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

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

	switch(new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_Renderer);
		m_Current_Screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
	defualt:;
	}
}


