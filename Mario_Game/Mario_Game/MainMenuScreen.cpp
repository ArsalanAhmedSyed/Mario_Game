#include "MainMenuScreen.h"
#include "Texture2D.h"

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupMenu();
}

MainMenuScreen::~MainMenuScreen()
{
	delete m_menuBackground_texture;
	m_menuBackground_texture = nullptr;

}

void MainMenuScreen::Render()
{
	m_menuBackground_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
}

bool MainMenuScreen::SetupMenu()
{
	bool success = true;

	m_menuBackground_texture = new Texture2D(m_renderer);
	if (!m_menuBackground_texture->LoadFromFile("Images/MainMenu.png"))
	{
		cout << "Could not load menu background!" << endl;
		success = false;
	}

	return success;
}