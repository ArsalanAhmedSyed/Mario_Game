#include "GameScreenLevel1.h"
#include "Texture2D.h"
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
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_Texture;
	m_background_Texture = nullptr;

	delete m_level_map;
	m_level_map = nullptr;

	delete mario_Character;
	mario_Character = nullptr;

	delete Luigi_Character;
	Luigi_Character = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	m_background_Texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);
	mario_Character->Render();
	Luigi_Character->Render();
	m_pow_block->Render();
	Koopa_Character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
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
			m_shake_time = false;
			m_screenShake = false;
			m_background_yPos = 0.0f;
		}
	}

	if (Collisions::Instance()->Circle(mario_Character->GetCollisionCircle(), Luigi_Character->GetCollisionCircle()))
	{
		cout << "Circle Hit!" << endl;
	}

	if (Collisions::Instance()->Box(mario_Character->getCollisionBox(), Luigi_Character->getCollisionBox()))
	{
		cout << "Box Hit!" << endl;
	}

	mario_Character->Update(deltaTime, e);
	Luigi_Character->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	bool success = true;

	m_background_Texture = new Texture2D(m_Renderer);
	if (!m_background_Texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!" << endl;
		success = false;
	}

	SetLevelMap();

	m_pow_block = new PowBlock(m_Renderer, m_level_map);
	m_screenShake = false;
	m_background_yPos = 0.0f;

	mario_Character = new CharacterMario(m_Renderer, "Images/Mario.png", Vector2D(64, 330),m_level_map);
	Luigi_Character = new CharacterLuigi(m_Renderer, "Images/Luigi.png", Vector2D(100, 330), m_level_map);
	

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

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
	if (Collisions::Instance()->Box(mario_Character->getCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable() && m_screenShake == false)
		{
			if (mario_Character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario_Character->CancelJump();
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
	Koopa_Character = new CharacterKoopa(m_Renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
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
				if (m_enemies[i]->getPosition().x < (float)(-m_enemies[i]->getCollisionBox().width * 0.5f)
					|| m_enemies[i]->getPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->getCollisionBox().width * 0.5f))
				{
					m_enemies[i]->SetAlive(false);
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
					if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), mario_Character->GetCollisionCircle()))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
						}
						else
						{
							//kill mario
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
}