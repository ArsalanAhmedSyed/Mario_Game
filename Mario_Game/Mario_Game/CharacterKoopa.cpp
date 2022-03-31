#include "CharacterKoopa.h"
#include "constants.h"
#include <iostream>

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_Texture = new Texture2D(m_Renderer);
	if (!m_Texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_Position = start_position;

	m_injured = false;
	m_turn_anim = false;
	m_roll_anim = false;


	m_single_sprite_w = m_Texture->GetWidth() / frames;
	m_single_sprite_h = m_Texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void CharacterKoopa::Render()
{
	if (m_alive)
	{
		SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };
		SDL_Rect destRect = { (int)(m_Position.x), (int)(m_Position.y), m_single_sprite_w, m_single_sprite_h };

		if (m_facing_direction == FACING_RIGHT)
		{
			m_Texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
		}
		else
		{
			m_Texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
		}
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!m_injured)
	{
		if (!m_turn_anim && !m_roll_anim)
		{
			if (m_facing_direction == FACING_LEFT)
			{
				MoveLeft(deltaTime);
				RunAnimation(deltaTime);
			}
			else if (m_facing_direction == FACING_RIGHT)
			{
				MoveRight(deltaTime);
				RunAnimation(deltaTime);
			}
		}

		if (m_turn_anim)
		{
			TurnAnimation(deltaTime);
		}

		if (m_roll_anim)
		{
			RollOverAnimation(deltaTime);
		}
	}
	else
	{

		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;
		if (m_injured_time <= 0.0f)
		{
			m_injured = false;
			m_roll_anim = true;
		}
	}

	Character::Update(deltaTime, e);
}

void CharacterKoopa::TakeDamage()
{
	m_current_frame = 9;

	m_injured = true;
	m_injured_time = INJURED_TIME;

	Jump();
}

void CharacterKoopa::KeepOnScreen(float deltaTime)
{
	if (m_Position.x + m_Texture->GetWidth() / m_animation_frames > SCREEN_WIDTH)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_Position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_Position.x < 0)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_Position.x += deltaTime * MOVEMENT_SPEED;
	}
}

void CharacterKoopa::RunAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 4)
			m_current_frame = 0;
	}
}

void CharacterKoopa::TurnAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 8)
		{
			m_current_frame = 0;
			m_turn_anim = false;

			if (m_facing_direction == FACING_RIGHT)
			{
				m_facing_direction = FACING_LEFT;
			}
			else if (m_facing_direction == FACING_LEFT)
			{
				m_facing_direction = FACING_RIGHT;
			}
		}
	}
}

void CharacterKoopa::RollOverAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 14)
		{
			m_current_frame = 0;
			m_roll_anim = false;
		}
	}
}

void CharacterKoopa::MoveRight(float deltaTime)
{
	m_Position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterKoopa::MoveLeft(float deltaTime)
{
	m_Position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}