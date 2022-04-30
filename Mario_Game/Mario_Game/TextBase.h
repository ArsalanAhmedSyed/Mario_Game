#ifndef _TEXTBASE_H
#define _TEXTBASE_H

#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class TextRenderer;

class TextBase
{
public:
	TextBase(SDL_Renderer* renderer);
	~TextBase();

	void Render(int x, int y);
	void Update(float deltaTime, SDL_Event e);

	virtual void Loadtxt();

	void IncremrentScore(int addScore) { score += addScore; }

protected:
	string text;
	int score, old_score;
	TextRenderer* m_text_render;

private:
	SDL_Renderer* m_renderer;
};

#endif // !_TEXTBASE_H


