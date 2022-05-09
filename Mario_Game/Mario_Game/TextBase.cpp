#include "TextBase.h"

TextBase::TextBase(SDL_Renderer* renderer)
{
	m_renderer = renderer;

	//Initialize text renderer
	m_text_render = new TextRenderer(m_renderer);

	//Score Text to print
	score = 0;
	old_score = 0;
	m_text = "Score ";
}
TextBase::~TextBase()
{
	delete m_text_render;
	m_text_render = nullptr;
}

void TextBase::Render(int x, int y)
{
	//Render position 
	m_text_render->Render(x,y);
}

void TextBase::Update(float deltaTime, SDL_Event e)
{
	//Update score text
	if (score != old_score)
	{
		old_score = score;
		Loadtxt();
	}
}

void TextBase::Loadtxt() 
{
	//Render text
	m_text_render->LoadFont("Fonts/MarioFont.ttf",20, m_text + to_string(score), { 255,255,255 });
}
