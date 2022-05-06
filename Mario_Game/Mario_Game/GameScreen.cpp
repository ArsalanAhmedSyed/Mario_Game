#include "GameScreen.h"

using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_selected = false;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}
