#include "CharacterMario.h"
#include "Texture2D.h"
#include "constants.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
	m_Texture = new Texture2D(m_Renderer);
	if (!m_Texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_facing_direction = FACING_RIGHT;

	m_collision_radius = 15.0f;

}

CharacterMario::~CharacterMario()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void CharacterMario::Render()
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

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	AddGravity(deltaTime);
	if (m_jumping)
	{
		m_Position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
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

	switch (e.type)
	{
	case SDL_KEYDOWN:
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
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
		}
		break;
	}
}

void CharacterMario::MoveRight(float deltaTime)
{
	m_Position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}


void CharacterMario::MoveLeft(float deltaTime)
{
	m_Position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void CharacterMario::AddGravity(float deltaTime)
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

void CharacterMario::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}
