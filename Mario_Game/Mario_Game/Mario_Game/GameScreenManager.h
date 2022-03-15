#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltatime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* m_Renderer;
	GameScreen* m_Current_Screen;
};

#endif // !_GAMESCREENMANAGER_H



