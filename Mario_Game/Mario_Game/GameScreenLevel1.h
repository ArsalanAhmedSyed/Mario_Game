#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "Commons.h"
#include "GameScreen.h"
#include <vector>

class Texture2D;
class LevelMap;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

	std::vector<CharacterKoopa*> m_enemies;

private:
	bool SetUpLevel();
	void SetLevelMap();
	
	Texture2D* m_background_Texture;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	//Character* my_Character;
	CharacterMario* mario_Character;
	CharacterLuigi* Luigi_Character;
	CharacterKoopa* Koopa_Character;

	//ScreenShake
	bool m_screenShake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();
	

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

};

#endif // !_GAMESCREENLEVEL1_

