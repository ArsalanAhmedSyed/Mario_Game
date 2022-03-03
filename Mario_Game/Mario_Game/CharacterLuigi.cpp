#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_Texture = new Texture2D(m_Renderer);
	if (!m_Texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_facing_direction = FACING_LEFT;

	m_collision_radius = 15.0f;
}

CharacterLuigi::~CharacterLuigi()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void CharacterLuigi::Render()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	}
	else
	{
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
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

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			Jump();
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
		}
		break;
	}

	Character::Update(deltaTime, e);
}

void CharacterLuigi::MoveRight(float deltaTime)
{
	m_Position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterLuigi::MoveLeft(float deltaTime)
{
	m_Position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void CharacterLuigi::AddGravity(float deltaTime)
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

void CharacterLuigi::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}