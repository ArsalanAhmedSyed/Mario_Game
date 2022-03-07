#include "CharacterKoopa.h"
#include "constants.h"
#include <iostream>

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_Position = start_position;
	m_injured = false;

	m_single_sprite_w = m_Texture->GetWidth() / 2;
	m_single_sprite_h = m_Texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void CharacterKoopa::Render()
{
	int left = 0.0f;
	if (m_injured)
	{
		left = m_single_sprite_w;
	}

	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w,m_single_sprite_h };
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

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0f)
		{
			FlipRightwayUp();
		}
	}

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
	}
	else
	{
		m_facing_direction = FACING_RIGHT;
	}

	m_injured = false;

	Jump();
}
