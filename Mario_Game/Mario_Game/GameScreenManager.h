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

	//Change Screen by passing in enum to load specific screen
	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
	SoundEffect* m_play_music;

	bool m_gameplay;
	bool m_canChange;

	CHARACTER selectedCharacter;
};

#endif // !_GAMESCREENMANAGER_H