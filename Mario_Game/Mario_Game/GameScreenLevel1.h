#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include <vector>
#include <string>

using namespace std;

class Texture2D;
class TextBase;
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

	//Characters
	Character* mario;
	Character* luigi;
	CharacterKoopa* Koopa_Character;

	//Audio
	SoundEffect* m_sound;

	//Text
	TextBase* m_text;
	TextBase* m_cointxt;
	TextBase* m_gameOver_txt;

	bool m_render_gameOver_text;
	float m_gameover_text_timer;

	//Text functions
	void UpdateText(float deltaTime, SDL_Event e);
	void TextSetup();
	void RenderText();

	//Create Koopa
	std::vector<CharacterKoopa*> m_enemies;
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	float create_koopa_timer;

	//Setup level
	void SetUpLevel();
	void SetLevelMap();
	
	//ScreenShake
	bool m_screenShake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();

	//Coins
	std::vector<CoinCharacter*> m_coins;
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D postiion);

	void GameOver(float deltaTime, SDL_Event e);
	bool m_play_gameover_music;
	bool m_gameOver;
};

#endif // !_GAMESCREENLEVEL1_

