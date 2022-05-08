#include "LevelEndtxt.h"

LevelEndtxt::LevelEndtxt(SDL_Renderer* renderer) : TextBase(renderer)
{
	m_text = "LEVEL END";
}

LevelEndtxt::~LevelEndtxt() {}

void LevelEndtxt::Loadtxt()
{
	m_text_render->LoadFont("Fonts/MarioFont.ttf", 50, m_text, { 255,255,255 });
}
