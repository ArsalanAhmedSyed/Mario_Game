#include "GameScreen.h"
#include <iostream>

using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
}
GameScreen::~GameScreen()
{
	m_Renderer = nullptr;
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}
