#include "LevelEndtxt.h"

LevelEndtxt::LevelEndtxt(SDL_Renderer* renderer) : TextBase(renderer)
{
	//Text to print
	m_text = "LEVEL END";
}

LevelEndtxt::~LevelEndtxt() {}

void LevelEndtxt::Loadtxt()
{
	//Render text
	m_text_render->LoadFont("Fonts/MarioFont.ttf", 50, m_text, { 255,255,255 });
}
