#ifndef _ControlsScreen_H
#define _ControlsScreen_H

#include "GameScreen.h"

class Texture2D;

class ControlsScreen : GameScreen
{
public:
	ControlsScreen(SDL_Renderer* renderer);
	~ControlsScreen();

	void Render()override;

private:
	Texture2D* m_background_texture;

	bool SetUpControlsScreen();
};

#endif // !_ControlsScreen_H


