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
	//Clear the texture
	delete m_background_texture;
	m_background_texture = nullptr;
}

void SelectionScreen::Render()
{
	//Render background of character selection screen
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
			//Select mario
			m_character_select = MARIO;
			m_selected = true;
			break;
		case SDLK_l:
			//Select Luigi
			m_character_select = LUIGI;
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

	//Render Selection screen Background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/SelectionMenu.png"))
	{
		cout << "Failed to load selection screen background" << endl;
		success = false;
	}

	return success;
}
