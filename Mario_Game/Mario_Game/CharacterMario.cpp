#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map,int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_facing_direction = FACING_RIGHT;

	m_single_sprite_w = m_Texture->GetWidth() / frames;
	m_single_sprite_h = m_Texture->GetHeight();
}

CharacterMario::~CharacterMario() {}

void CharacterMario::Render()
{
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect desRect = { (int)(m_Position.x), (int)(m_Position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_Texture->Render(portion_of_sprite, desRect, SDL_FLIP_HORIZONTAL);
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_Texture->Render(portion_of_sprite, desRect, SDL_FLIP_NONE);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);

		if(!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);

		if(!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else if (m_jump_Anim)
	{
		m_current_frame = 4;
	}
	else
	{
		m_current_frame = 0;
	}

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

	//KeepOnScreen(deltaTime);
	Character::Update(deltaTime, e);
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

void CharacterMario::KeepOnScreen(float deltaTime)
{
	if (m_Position.x + m_Texture->GetWidth() / m_animation_frames > SCREEN_WIDTH)
	{
		m_facing_direction = FACING_RIGHT;
		m_Position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_Position.x < 0)
	{
		m_facing_direction = FACING_LEFT;
		m_Position.x += deltaTime * MOVEMENT_SPEED;
	}
}