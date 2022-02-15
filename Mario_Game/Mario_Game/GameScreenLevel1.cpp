#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_Texture;
	m_background_Texture = nullptr;

	delete my_Character;
	my_Character = nullptr;
}

void GameScreenLevel1::Render()
{
	m_background_Texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_Character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	my_Character->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	bool success = true;

	m_background_Texture = new Texture2D(m_Renderer);
	if (!m_background_Texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!" << endl;
		success = false;
	}

	my_Character = new Character(m_Renderer, "Images/Mario.png", Vector2D(64, 330));

	return success;
}
