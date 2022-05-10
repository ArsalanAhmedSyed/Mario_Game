#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreen.h"
#include "constants.h"
#include <vector>

class Texture2D;
class TextBase;
class LevelMap;
class Character;
class CoinCharacter;
class CharacterKoopa;
class PowBlock;
class SoundEffect;

class SelectionScreen;
class CharacterGoomba;
class LevelEndCharacter;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer, CHARACTER character_select);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;



private:
	//Classes
	Texture2D* m_background_Texture;
	LevelMap* m_level_map;

	//Characters
	Character* mario;
	Character* luigi;
	CoinCharacter* coin;

	//Mario & Luigi
	CHARACTER m_character_selected;
	void RenderCharacter();

	//Audio
	SoundEffect* m_sound;

	//Text
	TextBase* m_text;
	TextBase* m_cointxt;
	TextBase* m_gameOver_txt;
	TextBase* m_levelEnd_txt;

	//Text functions
	void UpdateText(float deltaTime, SDL_Event e);
	void TextSetup();
	void RenderText();

	//Create Koopa
	CharacterKoopa* Koopa_character;
	std::vector<CharacterKoopa*> m_Koopas;
	float create_koopa_timer;

	void UpdateKoopas(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);

	//Create Goomba
	CharacterGoomba* goomba_character;
	std::vector<CharacterGoomba*> m_Goombas;

	void UpdateGoombas(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction);

	//Setup level
	void SetUpLevel();
	void SetLevelMap();

	//ScreenShake/ Powblock
	PowBlock* m_pow_block;
	bool m_screenShake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();
	void UpdatePOWBlock();

	//Coins
	std::vector<CoinCharacter*> m_coins;
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoins(Vector2D postiion);

	//GameOver
	bool m_gameOver;
	bool m_play_gameover_music;
	bool m_render_gameOver_text;
	float m_gameover_text_timer;

	void GameOver(float deltaTime);  

	//Camera
	void UpdateCamera();
	SDL_Rect m_camera{ 0,0,0,0 };

	//Level end
	LevelEndCharacter* peech_character;
	bool m_levelEnd;
	void LevelEnd();
	
	void SetupEnemies();
	void SetupCoins();
};

#endif // !_GAMESCREENLEVEL2_H


