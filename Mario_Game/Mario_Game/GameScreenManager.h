#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include "Commons.h"

class GameScreen;
class SoundEffect;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltatime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_Current_Screen;
	SoundEffect* m_play_music;
};

#endif // !_GAMESCREENMANAGER_H