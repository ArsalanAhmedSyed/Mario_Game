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

class SelectionScreen;
class CharacterGoomba;
class LevelEndCharacter;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, CHARACTER character_select);
	~GameScreenLevel1();

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
	void RenderCharacter();
	CHARACTER m_character_selected;

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

	//Koopa veriables/ functions
	CharacterKoopa* Koopa_character;
	void UpdateKoopas(float deltaTime, SDL_Event e);

	//Goomba Functions/ veriables
	CharacterGoomba* goomba_character;
	std::vector<CharacterGoomba*> m_Goombas;
	void UpdateGoombas(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction);
	float create_Goomba_timer;
	bool m_spawn;

	//Setup level
	void SetUpLevel();
	void SetLevelMap();
	
	//ScreenShake/PowBlock
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
	void GameOver(float deltaTime);
	bool m_gameOver;
	bool m_play_gameover_music;
	bool m_render_gameOver_text;
	float m_gameover_text_timer;

	//Camera
	void UpdateCamera();
	SDL_Rect m_camera{ 0,0,0,0 };

	//Level End
	LevelEndCharacter* peech_character;
	void LevelEnd();
	bool m_levelEnd;

	void SetupCoins();
};

#endif // !_GAMESCREENLEVEL1_