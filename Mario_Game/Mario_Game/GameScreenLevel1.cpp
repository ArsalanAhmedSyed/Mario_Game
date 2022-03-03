#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
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
}

void GameScreenLevel1::Render()
{
	m_background_Texture->Render(Vector2D(), SDL_FLIP_NONE);
	mario_Character->Render();
	Luigi_Character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
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

	mario_Character = new CharacterMario(m_Renderer, "Images/Mario.png", Vector2D(64, 330),m_level_map);
	Luigi_Character = new CharacterLuigi(m_Renderer, "Images/Luigi.png", Vector2D(100, 330), m_level_map);

	

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
