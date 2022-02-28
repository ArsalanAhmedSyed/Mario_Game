#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "Commons.h"
#include "GameScreen.h"


class Texture2D;
class LevelMap;
class CharacterMario;
class CharacterLuigi;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	
	bool SetUpLevel();
	void SetLevelMap();
	
	Texture2D* m_background_Texture;
	LevelMap* m_level_map;

	//Character* my_Character;
	CharacterMario* mario_Character;
	CharacterLuigi* Luigi_Character;
};

#endif // !_GAMESCREENLEVEL1_

