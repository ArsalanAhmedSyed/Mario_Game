#include "Character.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_Renderer = renderer;
	m_Position = start_position;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;

	m_current_level_map = map;
}

Character::~Character()
{
	m_Renderer = nullptr;
}

void Character::SetPosition(Vector2D new_position) { m_Position = new_position; }

Vector2D Character::getPosition() { return m_Position; }

void Character::Render() {}

void Character::Update(float deltaTime, SDL_Event e)
{
	//collision position variables
	int centralX_position = (int)(m_Position.x + (m_Texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_Position.y + m_Texture->GetHeight()) / TILE_HEIGHT;

	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		// deal with gravity
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so can jump again
		m_can_jump = true;
	}
}

void Character::MoveLeft(float deltaTime) {}

void Character::MoveRight(float deltaTime) {}

void Character::AddGravity(float deltaTime) {}

void Character::Jump() {}



