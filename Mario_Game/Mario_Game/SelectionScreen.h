#ifndef _SELECTIONSCREEN_H
#define _SELECTIONSCREEN_H

#include "GameScreen.h"

class Texture2D;
class GameScreenLevel1;

class SelectionScreen : GameScreen
{
public:
	SelectionScreen(SDL_Renderer* renderer);
	~SelectionScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;

	GameScreenLevel1* m_screen_level1;

	

	bool SetupSelection();
};

#endif // !_SELECTIONSCREEN_H



