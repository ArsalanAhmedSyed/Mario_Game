#include "GameScreenManager.h"
#include "MainMenuScreen.h"
#include "SoundEffect.h"
#include "Texture2D.h"


MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupMenu();
}

MainMenuScreen::~MainMenuScreen()
{
	delete m_menuBackground_texture;
	m_menuBackground_texture = nullptr;

	delete m_music;
	m_music = nullptr;

	delete m_gameManger_screen;
	m_gameManger_screen = nullptr;
}

void MainMenuScreen::Render()
{
	m_menuBackground_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
}

void MainMenuScreen::Update(float deltaTime, SDL_Event e) {}

bool MainMenuScreen::SetupMenu()
{
	bool success = true;

	m_menuBackground_texture = new Texture2D(m_renderer);
	if (!m_menuBackground_texture->LoadFromFile("Images/MainMenu.png"))
	{
		cout << "Could not load background!" << endl;
		success = false;
	}

	m_music = new SoundEffect();

	return success;
}