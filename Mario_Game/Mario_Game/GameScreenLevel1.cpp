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
#include <iostream>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();
	create_koopa_timer = 15.0f;
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

	delete coin;
	coin = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();
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

	if(coin->GetAlive())
		coin->Render();

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
		cout << "Circle Hit!" << endl;
	}

	if (Collisions::Instance()->Box(mario->getCollisionBox(), luigi->getCollisionBox()))
	{
		cout << "Box Hit!" << endl;
	}

	//Characters
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	//Objects
	coin->Update(deltaTime, e);
	CoinCollision();
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

	m_background_Texture = new Texture2D(m_Renderer);
	if (!m_background_Texture->LoadFromFile("Images/Background.png"))
	{
		cout << "Failed to load background texture!" << endl;
		success = false;
	}

	SetLevelMap();

	//powblock render
	m_pow_block = new PowBlock(m_Renderer, m_level_map);

	#pragma region Character Render
	mario = new CharacterMario(m_Renderer, "Images/MarioSprite.png", Vector2D(64, 330), m_level_map, 6);
	luigi = new CharacterLuigi(m_Renderer, "Images/Luigi.png", Vector2D(100, 330), m_level_map, 1);

	//objects
	coin = new CoinCharacter(m_Renderer, "Images/Coin.png", Vector2D(150, 350), m_level_map,3);

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
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
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
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
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
	Koopa_Character = new CharacterKoopa(m_Renderer, "Images/Koopa.png", m_level_map, position, direction, speed, 1);
	m_enemies.push_back(Koopa_Character);
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

			//check to see if enemy collides with player 
			if ((m_enemies[i]->getPosition().y > 300.0f || m_enemies[i]->getPosition().y <= 64.0f && (m_enemies[i]->getPosition().x < 64.0f
				|| m_enemies[i]->getPosition().x > SCREEN_WIDTH - 96.0f)))
			{
				//ignore collisions if behind pipe
			}
			else
			{
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
						if (mario->GetAlive())
						{
							//Kill mario
							mario->SetAlive(false);
							cout << "You died!" << endl;
						}
					}
				}
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

void GameScreenLevel1::CoinCollision()
{
	if (Collisions::Instance()->Circle(mario->GetCollisionCircle(), coin->GetCollisionCircle()))
	{
		if (coin->GetAlive())
		{
			cout << "Coin Collected!" << endl;
			cout << "Score increased!" << endl;
			coin->SetAlive(false);
		}
	}
}