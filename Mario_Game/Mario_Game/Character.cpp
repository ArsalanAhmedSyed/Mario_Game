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
	AddGravity(deltaTime);
	if (m_jumping)
	{
		m_Position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//if (m_jump_force <= 0.0f)
		//{
		//	//m_jumping = false;
		//}
	}

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
			m_moving_right = true;
			break;
		case SDLK_UP:
			Jump();
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

void Character::AddGravity(float deltaTime)
{
	if (m_Position.y + m_Texture->GetHeight() <= SCREEN_HEIGHT)
	{
		m_Position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_Position.y = SCREEN_HEIGHT - m_Texture->GetHeight();
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (m_can_jump)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}


float Character::GetCollisionRaidus()
{
	return m_collision_radius;
}

