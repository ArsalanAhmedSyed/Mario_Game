#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "Commons.h"
#include "GameScreen.h"
#include <vector>

class Texture2D;
class LevelMap;
class Character;
class CoinCharacter;
class CharacterKoopa;
class PowBlock;
class SoundEffect;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

private:
	//Classes
	Texture2D* m_background_Texture;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	CoinCharacter* coin;

	Character* mario;
	Character* luigi;
	CharacterKoopa* Koopa_Character;

	SoundEffect* m_sound;

	//Create Koopa
	std::vector<CharacterKoopa*> m_enemies;
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	float create_koopa_timer;

	//Setup level
	bool SetUpLevel();
	void SetLevelMap();
	
	//ScreenShake
	bool m_screenShake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();

	//collison checks
	void UpdateCoins();
	std::vector<CoinCharacter*> m_coins;
	void CreateCoins(Vector2D postiion);
};

#endif // !_GAMESCREENLEVEL1_

