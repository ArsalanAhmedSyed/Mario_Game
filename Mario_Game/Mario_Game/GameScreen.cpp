#include "GameScreen.h"

using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_selected = false;
	m_character_select = LUIGI;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) 
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_m:
			m_character_select = MARIO;
			cout << "Chracter Mario select update!" << endl;
			break;
		case SDLK_l:
			m_character_select = LUIGI;
			cout << "Chracter Luigi select update!" << endl;
			break;
		}
		break;
	default:
		break;
	}
}
