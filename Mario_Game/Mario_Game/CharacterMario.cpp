#include "CharacterMario.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map,int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_facing_direction = FACING_RIGHT;

	m_single_sprite_w = m_texture->GetWidth() / frames;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterMario::~CharacterMario() {}

void CharacterMario::Render(SDL_Rect camera_rect)
{
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect desRect = { (int)(m_position.x - camera_rect.x), (int)(m_position.y - camera_rect.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, desRect, SDL_FLIP_HORIZONTAL);
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(portion_of_sprite, desRect, SDL_FLIP_NONE);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left && !m_kill_player)
	{
		MoveLeft(deltaTime);

		if(!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else if (m_moving_right && !m_kill_player)
	{
		MoveRight(deltaTime);

		if(!m_jump_Anim)
			RunAnimation(deltaTime);
	}
	else
	{
		m_current_frame = 0;
	}



	if (m_jump_Anim && !m_kill_player)
	{
		m_current_frame = 4;
	}

	if (m_kill_player)
	{
		m_current_frame = 5;
		Jump();
		m_kill_timer -= deltaTime;
		if (m_kill_timer <= 0)
		{
			m_alive = false;
		}
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
	m_position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterMario::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void CharacterMario::KeepOnScreen(float deltaTime)
{
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > LEVEL_WIDTH)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_position.x < 0)
	{
		m_facing_direction = FACING_LEFT;
		m_position.x += deltaTime * MOVEMENT_SPEED;
	}
}