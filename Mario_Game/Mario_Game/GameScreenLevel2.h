#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreen.h"

class Texture2D;
class LevelMap;
class Character;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	Texture2D* m_background_Texture;
	LevelMap* m_level_map;
	Character* mario;

	void SetLevelMap();
	bool SetUpLevel();

};

#endif // !_GAMESCREENLEVEL2_H


