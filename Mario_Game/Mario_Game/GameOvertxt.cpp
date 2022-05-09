#include "GameOvertxt.h"

GameOvertxt::GameOvertxt(SDL_Renderer* renderer) : TextBase(renderer) 
{
	//Text to print out
	m_text = "GAMEOVER";
}

GameOvertxt::~GameOvertxt() {}

void GameOvertxt::Loadtxt()
{
	//Render text
	m_text_render->LoadFont("Fonts/MarioFont.ttf", 50, m_text, { 255,255,255 });
}
