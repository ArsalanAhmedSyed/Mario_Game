#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "TextBase.h"
#include "Character.h"
#include "CoinCharacter.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "SoundEffect.h"
#include "Cointxt.h"
#include "GameOvertxt.h"
#include "CharacterGoomba.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, CHARACTER character_select) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();

	create_koopa_timer = 10.0f;

	m_shake_time = 0.0f;
	m_wobble = 0.0f;
	m_background_yPos = 0.0f;

	m_play_gameover_music = true;
	m_gameover_text_timer = 1.5f;

	m_character_selected = character_select;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_Texture;
	m_background_Texture = nullptr;

	delete m_level_map;
	m_level_map = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	delete m_sound;
	m_sound = nullptr;

	delete m_text;
	m_text = nullptr;

	delete m_cointxt;
	m_cointxt = nullptr;

	delete m_gameOver_txt;
	m_gameOver_txt = nullptr;

	m_enemies.clear();

	m_coins.clear();
}

void GameScreenLevel1::Render()
{
	m_background_Texture->Render(Vector2D(0,m_background_yPos),m_camera, SDL_FLIP_NONE);
	m_pow_block->Render(m_camera);

	m_level_map->DrawMap(m_camera);

	//Render The text
	RenderText();

	RenderCharacter();

	if (m_goomba->GetAlive())
		m_goomba->Render(m_camera);
	
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render(m_camera);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render(m_camera);
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	UpdateCamera();

	#pragma region ScreenShake
	if (m_screenShake)
	{
		//start screenshake
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//End shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_screenShake = false;
			m_shake_time = 0.0f;
			m_background_yPos = 0.0f;
		}
	}
	#pragma endregion 

	if (Collisions::Instance()->Circle(mario->GetCollisionCircle(), luigi->GetCollisionCircle()))
	{
		//cout << "Circle Hit!" << endl;
	}

	if (Collisions::Instance()->Box(mario->getCollisionBox(), luigi->getCollisionBox()))
	{
		//cout << "Box Hit!" << endl;
	}

	//Characters
	if(m_character_selected == MARIO)
		mario->Update(deltaTime, e);
	if(m_character_selected == LUIGI)
		luigi->Update(deltaTime, e);

	//GameOver Check
	if (!mario->GetAlive() && !luigi->GetAlive())
		GameOver(deltaTime);

	//Objects
	UpdateCoins(deltaTime,e);
	UpdatePOWBlock();

	//Update the text
	UpdateText(deltaTime,e);

	m_goomba->Update(deltaTime, e);

	//Enemies
	#pragma region KoopaUpdate

	UpdateEnemies(deltaTime, e);
	if (!m_gameOver)
	{
		create_koopa_timer -= deltaTime;
		if (create_koopa_timer <= 0)
		{
			cout << "koopa created!" << endl;
			CreateKoopa(Vector2D(800, 330), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(700, 330), FACING_LEFT, KOOPA_SPEED);
			create_koopa_timer = 10.0f;
		}
	}
	#pragma endregion
	GameScreen::Update(deltaTime,e);
}

void GameScreenLevel1::SetUpLevel()
{
	m_background_Texture = new Texture2D(m_renderer);
	if (!m_background_Texture->LoadFromFile("Images/test.png"))
	{
		cout << "Failed to load background texture!" << endl;
	}

	m_sound = new SoundEffect();
	if(m_sound == nullptr)
	{
		cout << "Failed to initalize the sound" << endl;
	}

	TextSetup();

	SetLevelMap();

	//powblock render
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	#pragma region Character Render
	mario = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 330), m_level_map, 6);
	luigi = new CharacterLuigi(m_renderer, "Images/LuigiSprite.png", Vector2D(100, 330), m_level_map, 6);

	m_goomba = new CharacterGoomba(m_renderer, "Images/GoombaSprite.png", m_level_map, Vector2D(200, 30), FACING_RIGHT, KOOPA_SPEED, 11.5);

	//objects
	CreateCoins(Vector2D(150, 340));
	CreateCoins(Vector2D(100, 340));
	CreateCoins(Vector2D(400, 340));
	CreateCoins(Vector2D(170, 340));
	CreateCoins(Vector2D(400, 340));

	//Enemies
	CreateKoopa(Vector2D(400, 330), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(625, 330), FACING_LEFT, KOOPA_SPEED);
	#pragma endregion
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
											{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//Set the new one
	m_level_map = new LevelMap(map, m_renderer);
}

void GameScreenLevel1::TextSetup()
{
	m_text = new TextBase(m_renderer);
	m_text->Loadtxt();

	m_cointxt = new Cointxt(m_renderer);
	m_cointxt->Loadtxt();

	m_gameOver_txt = new GameOvertxt(m_renderer);
	m_gameOver_txt->Loadtxt();
}

void GameScreenLevel1::UpdateText(float deltaTime,SDL_Event e)
{
	m_text->Update(deltaTime, e);
	m_cointxt->Update(deltaTime, e);
	m_gameOver_txt->Update(deltaTime, e);
}

void GameScreenLevel1::RenderText()
{
	if (m_render_gameOver_text)
		m_gameOver_txt->Render(66, 108);

	m_text->Render(70, 10);
	m_cointxt->Render(300, 10);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (m_character_selected == MARIO)
	{
		if (Collisions::Instance()->Box(mario->getCollisionBox(), m_pow_block->GetCollisionBox()))
		{
			if (m_pow_block->IsAvailable())
			{
				if (mario->IsJumping())
				{
					m_sound->Play(POWBLOCK);
					DoScreenShake();
					m_pow_block->TakeHit();
					mario->CancelJump();
				}
			}
		}
	}
	
	if (m_character_selected == LUIGI)
	{
		if (Collisions::Instance()->Box(luigi->getCollisionBox(), m_pow_block->GetCollisionBox()))
		{
			if (m_pow_block->IsAvailable())
			{
				if (luigi->IsJumping())
				{
					m_sound->Play(POWBLOCK);
					DoScreenShake();
					m_pow_block->TakeHit();
					luigi->CancelJump();
				}
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenShake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	Koopa_Character = new CharacterKoopa(m_renderer, "Images/KoopaSprite.png", m_level_map, position, direction, speed, 15);
	m_enemies.push_back(Koopa_Character);
}

void GameScreenLevel1::CreateCoins(Vector2D position)
{
	coin = new CoinCharacter(m_renderer, "Images/Coin.png", position, m_level_map, 3);
	m_coins.push_back(coin);
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;

		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->getPosition().y > 300.0f)
			{
				//is the enemy off screen to the left/right?
				if (m_enemies[i]->getPosition().x < (float)(-m_enemies[i]->getCollisionBox().width * 0.5)
					|| m_enemies[i]->getPosition().x > LEVEL_WIDTH - (float)(m_enemies[i]->getCollisionBox().width * 0.5))
				{
					m_enemies[i]->SetAlive(false);
				}

			}

			//now update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with screen edge
			if ((m_enemies[i]->getPosition().y > 500.0f || m_enemies[i]->getPosition().y <= 64.0f && (m_enemies[i]->getPosition().x < 64.0f
				|| m_enemies[i]->getPosition().x > LEVEL_WIDTH - 96.0f)))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				#pragma region Mario and Luigi collision

				if (m_character_selected == MARIO)
				{
					//Check Collision between koopa and mario
					if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), mario->GetCollisionCircle()))
					{
						if (m_enemies[i]->GetInjured())
						{
							if (m_enemies[i]->GetAlive())
							{
								m_enemies[i]->SetAlive(false);
								//Increase score
								m_text->IncremrentScore(200);
							}
						}
						else
						{
							if (mario->GetAlive() && !mario->GetKill())
							{
								//Kill mario
								if (luigi->GetAlive())
								{
									m_sound->Play(DEATH);
								}
								else
								{
									m_sound->Play(GAMEOVER);
								}

								mario->CancelJump();
								//Take away lives
								mario->setKill(true);
							}
						}
					}
				}

				if (m_character_selected == LUIGI)
				{
					if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), luigi->GetCollisionCircle()))
					{
						if (m_enemies[i]->GetInjured())
						{
							if (m_enemies[i]->GetAlive())
							{
								m_enemies[i]->SetAlive(false);
								//Increase score
								m_text->IncremrentScore(200);
							}
						}
						else
						{
							if (luigi->GetAlive() && !luigi->GetKill())
							{
								//Kill luigi
								if (mario->GetAlive())
								{
									m_sound->Play(DEATH);
								}
								else
								{
									m_sound->Play(GAMEOVER);
								}

								luigi->CancelJump();
								//Take away lives
								luigi->setKill(true);
							}
						}
					}
				}
				
				#pragma endregion
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;

		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (m_character_selected == MARIO)
			{
				if (Collisions::Instance()->Circle(mario->GetCollisionCircle(), m_coins[i]->GetCollisionCircle()))
				{
					if (m_coins[i]->GetAlive() && !mario->GetKill())
					{
						m_sound->Play(COIN);
						//Increase score
						m_text->IncremrentScore(50);
						m_cointxt->IncremrentScore(1);
						m_coins[i]->SetAlive(false);
					}
				}
			}
			
			if (m_character_selected == LUIGI)
			{
				if (Collisions::Instance()->Circle(luigi->GetCollisionCircle(), m_coins[i]->GetCollisionCircle()))
				{
					if (m_coins[i]->GetAlive() && !luigi->GetKill())
					{
						m_sound->Play(COIN);
						//Increase score
						m_text->IncremrentScore(50);
						m_cointxt->IncremrentScore(1);
						m_coins[i]->SetAlive(false);
					}
				}
			}
			
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::GameOver(float deltaTime)
{
	m_gameOver = true;

	if (m_play_gameover_music)
	{
		m_sound->PlayMusic(STOP_MUSIC);
		m_play_gameover_music = false;
	}

	m_gameover_text_timer -= deltaTime;
	if (m_gameover_text_timer <= 0)
	{
		m_render_gameOver_text = true;
	}
}

void GameScreenLevel1::RenderCharacter()
{
	//Characters render
	if (m_character_selected == MARIO)
	{
		luigi->SetAlive(false);
		if (mario->GetAlive())
			mario->Render(m_camera);
	}
	
	if (m_character_selected == LUIGI)
	{
		mario->SetAlive(false);
		if (luigi->GetAlive())
			luigi->Render(m_camera);
	}
}

void GameScreenLevel1::UpdateCamera()
{
	m_camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	if(m_character_selected == MARIO)
		m_camera.x = mario->getPosition().x - SCREEN_WIDTH / 2;
	if(m_character_selected == LUIGI)
		m_camera.x = luigi->getPosition().x - SCREEN_WIDTH / 2;

	if (m_camera.x <= 0)
	{
		m_camera.x = 0;
	}
	else if (m_camera.x >= LEVEL_WIDTH - m_camera.w)
	{
		m_camera.x = LEVEL_WIDTH - m_camera.w;
	}
}