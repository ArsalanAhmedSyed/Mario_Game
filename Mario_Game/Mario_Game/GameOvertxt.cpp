#include "GameOvertxt.h"
#include "TextRenderer.h"

GameOvertxt::GameOvertxt(SDL_Renderer* renderer) : TextBase(renderer) 
{
	text = "GAMEOVER";
}

GameOvertxt::~GameOvertxt() {}

void GameOvertxt::Loadtxt()
{
	m_text_render->LoadFont("Fonts/MarioFont.ttf", 50, text, { 0,0,0 });
}
