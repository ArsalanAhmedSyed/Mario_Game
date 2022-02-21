#include "Character.h"
#include "Texture2D.h"
#include "constants.h"


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_Renderer = renderer;
	m_Position = start_position;

	m_Texture = new Texture2D(m_Renderer);
	if (!m_Texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;
}

Character::~Character()
{
	m_Renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	}
	else
	{
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	SDL_PollEvent(&e);

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			//m_Position.x += 1;
			//m_facing_direction = FACING_RIGHT;
			m_moving_right = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
		}
	}
	
}

void Character::SetPosition(Vector2D new_position)
{
	m_Position = new_position;
}

Vector2D Character::getPosition()
{
	return m_Position;
}

void Character::MoveLeft(float deltaTime)
{
	m_Position.x -= deltaTime* MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_Position.x += deltaTime* MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

float Character::GetCollisionRaidus()
{
	return m_collision_radius;
}
