#ifndef _MAINMENUSCREEN_H
#define _MAINMENUSCREEN_H

#include "GameScreen.h"

class Texture2D;
class SoundEffect;
class GameScreenManager;

class MainMenuScreen :	GameScreen
{
public:
	MainMenuScreen(SDL_Renderer* renderer);
	~MainMenuScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	
private:
	Texture2D* m_menuBackground_texture;
	SoundEffect* m_music;
	GameScreenManager* m_gameManger_screen;

	bool SetupMenu();
};
#endif // !_MAINMENUSCREEN_H