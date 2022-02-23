#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "Commons.h"
#include "GameScreen.h"


class Texture2D;
//class Character;

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
	Texture2D* m_background_Texture;
	bool SetUpLevel();
	
	//Character* my_Character;
	CharacterMario* mario_Character;
	CharacterLuigi* Luigi_Character;
};

#endif // !_GAMESCREENLEVEL1_

