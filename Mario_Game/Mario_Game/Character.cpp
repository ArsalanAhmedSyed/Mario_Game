#include "Character.h"


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_Renderer = renderer;
	m_Position = start_position;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;
}

Character::~Character()
{
	m_Renderer = nullptr;
}


void Character::SetPosition(Vector2D new_position)
{
	m_Position = new_position;
}

Vector2D Character::getPosition()
{
	return m_Position;
}

float Character::GetCollisionRaidus() { return m_collision_radius; }

void Character::Render() {}

void Character::Update(float deltaTime, SDL_Event e) {}

void Character::MoveLeft(float deltaTime) {}

void Character::MoveRight(float deltaTime) {}

void Character::AddGravity(float deltaTime) {}

void Character::Jump() {}



