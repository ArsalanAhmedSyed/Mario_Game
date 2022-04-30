#include "TextBase.h"
#include "TextRenderer.h"

TextBase::TextBase(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_text_render = new TextRenderer(m_renderer);

	score = 0;
	old_score = 0;
	text = "Score ";
}
TextBase::~TextBase()
{
	delete m_text_render;
	m_text_render = nullptr;
}

void TextBase::Render(int x, int y)
{
	m_text_render->Render(x,y);
}

void TextBase::Update(float deltaTime, SDL_Event e)
{
	if (score != old_score)
	{
		old_score = score;
		Loadtxt();
	}
}

void TextBase::Loadtxt() 
{
	m_text_render->LoadFont("Fonts/MarioFont.ttf",20, text + to_string(score), { 0,0,0 });
}
