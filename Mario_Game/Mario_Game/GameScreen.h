#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include "Commons.h"
#include <iostream>

using namespace std;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	bool GetSelection() { return m_selected; }
	void SetSelection(bool change) { m_selected = change; }

protected:
	SDL_Renderer* m_renderer;
	CHARACTER m_character_select;
	bool m_selected;
	bool character_select;
};

#endif // !_GAMESCREEN_H


