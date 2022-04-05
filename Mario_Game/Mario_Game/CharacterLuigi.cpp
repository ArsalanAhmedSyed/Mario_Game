#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_facing_direction = FACING_RIGHT;

	m_single_sprite_w = m_Texture->GetWidth() / 6;
	m_single_sprite_h = m_Texture->GetHeight();
}

CharacterLuigi::~CharacterLuigi() {}

void CharacterLuigi::Render()
{
	
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect desRect = { (int)(m_Position.x), (int)(m_Position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_Texture->Render(portion_of_sprite, desRect, SDL_FLIP_NONE);
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_Texture->Render(portion_of_sprite, desRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{

	if (m_moving_left && !m_kill_player)
	{
		MoveLeft(deltaTime);

		if (!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else if (m_moving_right && !m_kill_player)
	{
		MoveRight(deltaTime);

		if (!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else
	{
		m_current_frame = 0;
	}

	if (m_kill_player)
	{
		m_current_frame = 5;
		m_sound->Play(DEATH);

		m_kill_timer -= deltaTime;
		if (m_kill_timer <= 0)
		{
			m_alive = false;
		}
	}

	if (m_jump_Anim && !m_kill_player)
	{
		m_current_frame = 4;
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
			if (!m_kill_player)
			{
				Jump();
				if (m_play_jump_audio)
				{
					m_sound->Play(JUMP);
				}
			}
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

void CharacterLuigi::MoveLeft(float deltaTime)
{
	m_Position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterLuigi::MoveRight(float deltaTime)
{
	m_Position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}