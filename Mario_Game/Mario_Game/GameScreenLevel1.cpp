#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "CoinCharacter.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "SoundEffect.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();
	create_koopa_timer = 10.0f;

	m_shake_time = 0.0f;
	m_wobble = 0.0f;
	m_background_yPos = 0.0f;
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

	m_enemies.clear();

	m_coins.clear();
}

void GameScreenLevel1::Render()
{
	m_background_Texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);
	m_pow_block->Render();

	//Characters render
	if(mario->GetAlive())
		mario->Render();

	if(luigi->GetAlive())
		luigi->Render();
	
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
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
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	//Objects
	UpdateCoins(deltaTime,e);
	UpdatePOWBlock();

	//Enemies
	UpdateEnemies(deltaTime, e);
	create_koopa_timer -= deltaTime;
	if (create_koopa_timer <= 0)
	{
		cout << "koopa created!" << endl;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		create_koopa_timer = 5.f;
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	bool success = true;

	m_background_Texture = new Texture2D(m_renderer);
	if (!m_background_Texture->LoadFromFile("Images/Background.png"))
	{
		cout << "Failed to load background texture!" << endl;
		success = false;
	}

	SetLevelMap();

	m_sound = new SoundEffect();
	if(m_sound == nullptr)
	{
		cout << "Failed to initalize the sound" << endl;
		success = false;
	}

	//powblock render
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	#pragma region Character Render
	mario = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 330), m_level_map, 6);
	luigi = new CharacterLuigi(m_renderer, "Images/LuigiSprite.png", Vector2D(100, 330), m_level_map, 6);

	//SHOULD I DO THIS ????????????????
	if (mario == nullptr || luigi == nullptr)
	{
		cout << "Failed to Create characters" << endl;
		success = false;
	}

	//objects
	CreateCoins(Vector2D(150, 350));
	CreateCoins(Vector2D(100, 250));
	CreateCoins(Vector2D(400, 250));
	CreateCoins(Vector2D(170, 10));
	CreateCoins(Vector2D(400, 10));

	//Enemies
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	#pragma endregion

	return success;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//Set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock()
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
					|| m_enemies[i]->getPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->getCollisionBox().width * 0.5))
				{
					m_enemies[i]->SetAlive(false);
				}

			}

			//now update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with screen edge
			if ((m_enemies[i]->getPosition().y > 500.0f || m_enemies[i]->getPosition().y <= 64.0f && (m_enemies[i]->getPosition().x < 64.0f
				|| m_enemies[i]->getPosition().x > SCREEN_WIDTH - 96.0f)))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				#pragma region Mario and Luigi collision
				//Check Collision between koopa and mario
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), mario->GetCollisionCircle()))
				{
					if (m_enemies[i]->GetInjured())
					{
						if (m_enemies[i]->GetAlive())
						{
							m_enemies[i]->SetAlive(false);
							cout << "Add score!" << endl;
						}
					}
					else
					{
						if (mario->GetAlive() && !mario->GetKill())
						{
							//Kill mario
							m_sound->Play(DEATH);
							mario->CancelJump();
							//Take away lives
							mario->setKill(true);
							
						}
					}
				}

				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), luigi->GetCollisionCircle()))
				{
					if (m_enemies[i]->GetInjured())
					{
						if (m_enemies[i]->GetAlive())
						{
							m_enemies[i]->SetAlive(false);
							cout << "Add score!" << endl;
						}
					}
					else
					{
						if (luigi->GetAlive() && !luigi->GetKill())
						{
							//Kill mario
							m_sound->Play(DEATH);
							luigi->CancelJump();
							//Take away lives
							luigi->setKill(true);
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

			if (Collisions::Instance()->Circle(mario->GetCollisionCircle(), m_coins[i]->GetCollisionCircle()))
			{
				if (m_coins[i]->GetAlive() && !mario->GetKill())
				{
					m_sound->Play(COIN);
					cout << "Coin Collected!" << endl;
					cout << "Score increased!" << endl;
					m_coins[i]->SetAlive(false);
				}
			}

			if (Collisions::Instance()->Circle(luigi->GetCollisionCircle(), m_coins[i]->GetCollisionCircle()))
			{
				if (m_coins[i]->GetAlive() && !luigi->GetKill())
				{
					m_sound->Play(COIN);
					cout << "Coin Collected!" << endl;
					cout << "Score increased!" << endl;
					m_coins[i]->SetAlive(false);
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