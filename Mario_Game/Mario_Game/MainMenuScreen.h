#ifndef _MAINMENUSCREEN_H
#define _MAINMENUSCREEN_H

#include "GameScreen.h"

class Texture2D;

class MainMenuScreen :	GameScreen
{
public:
	MainMenuScreen(SDL_Renderer* renderer);
	~MainMenuScreen();

	void Render() override;
	
private:
	Texture2D* m_menuBackground_texture;

	bool SetupMenu();
};
#endif // !_MAINMENUSCREEN_H