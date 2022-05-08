#include "GameOvertxt.h"

GameOvertxt::GameOvertxt(SDL_Renderer* renderer) : TextBase(renderer) 
{
	m_text = "GAMEOVER";
}

GameOvertxt::~GameOvertxt() {}

void GameOvertxt::Loadtxt()
{
	m_text_render->LoadFont("Fonts/MarioFont.ttf", 50, m_text, { 255,255,255 });
}
