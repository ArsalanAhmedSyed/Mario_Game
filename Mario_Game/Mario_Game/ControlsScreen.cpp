#include "ControlsScreen.h"
#include "Texture2D.h"


ControlsScreen::ControlsScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpControlsScreen();
}

ControlsScreen::~ControlsScreen()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void ControlsScreen::Render()
{
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

bool ControlsScreen::SetUpControlsScreen()
{
	bool success = true;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Controls.png"))
	{
		cout << "Could not load Controls Image!" << endl;
		success = false;
	}

	return success;
}