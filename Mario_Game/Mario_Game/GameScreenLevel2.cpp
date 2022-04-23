#include "GameScreenLevel2.h"
#include "Texture2D.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_Texture;
	m_background_Texture = nullptr;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{

}

void GameScreenLevel2::Render()
{
	m_background_Texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

bool GameScreenLevel2::SetUpLevel()
{
	bool success = true;
	
	m_background_Texture = new Texture2D(m_renderer);
	if (!m_background_Texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture" << endl;
		success = false;
	}

	return success;
}