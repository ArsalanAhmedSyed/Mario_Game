#include "SelectionScreen.h"
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;


SelectionScreen::SelectionScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupSelection();
}

SelectionScreen::~SelectionScreen()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void SelectionScreen::Render()
{
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

void SelectionScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_m:
			m_character_select = MARIO;

			cout << "Chracter Mario select update!" << endl;
			m_selected = true;
			break;
		case SDLK_l:
			m_character_select = LUIGI;
			cout << "Chracter Luigi select update!" << endl;
			m_selected = true;
			break;
		}
		break;
	default:
		break;
	}
}

bool SelectionScreen::SetupSelection()
{
	bool success = true;

	//m_screen_level1 = new GameScreenLevel1(m_renderer, m_character_select);

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load selection screen background" << endl;
		success = false;
	}

	return success;
}
