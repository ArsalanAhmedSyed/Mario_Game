#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "Character.h"
#include "CharacterMario.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;	
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_Texture;
	m_background_Texture = nullptr;

	delete m_level_map;
	m_level_map = nullptr;

	delete mario;
	mario = nullptr;
}

void GameScreenLevel2::Render()
{
	m_background_Texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	m_level_map->DrawMap();

	if (mario->GetAlive())
		mario->Render(m_camera);
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);

	UpdateCamera();
}

bool GameScreenLevel2::SetUpLevel()
{
	bool success = true;
	
	m_background_Texture = new Texture2D(m_renderer);
	if (!m_background_Texture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture" << endl;
		success = false;
	}

	SetLevelMap();

	mario = new CharacterMario(m_renderer, "Images/MarioSprite.png", Vector2D(64, 330), m_level_map, 6);

	return success;
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };


	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//Set the new one
	m_level_map = new LevelMap(map, m_renderer);
}

void GameScreenLevel2::UpdateCamera()
{
	m_camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	m_camera.x = mario->getPosition().x - SCREEN_WIDTH;
	if (m_camera.x <= 0)
	{
		m_camera.x = 0;
	}
	else if (m_camera.x >= LEVEL_WIDTH - m_camera.w)
	{
		m_camera.x = LEVEL_WIDTH - m_camera.w;
	}
}