#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "CharacterMario.h"
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

	delete mario_Character;
	mario_Character = nullptr;
}

void GameScreenLevel1::Render()
{
	m_background_Texture->Render(Vector2D(), SDL_FLIP_NONE);
	mario_Character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario_Character->Update(deltaTime, e);
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

	mario_Character = new CharacterMario(m_Renderer, "Images/Mario.png", Vector2D(64, 330));

	return success;
}
