#include "CharacterKoopa.h"
#include "constants.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_injured = false;
	m_turn_anim = false;
	m_roll_anim = false;


	m_single_sprite_w = m_texture->GetWidth() / frames;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa() {}

void CharacterKoopa::Render(SDL_Rect rect)
{
	if (m_alive)
	{
		SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };
		SDL_Rect destRect = { (int)(m_position.x - rect.x), (int)(m_position.y - rect.y), m_single_sprite_w, m_single_sprite_h };

		if (m_facing_direction == FACING_RIGHT)
		{
			m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
		}
		else
		{
			m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
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
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > LEVEL_WIDTH)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_position.x < 0)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_position.x += deltaTime * MOVEMENT_SPEED;
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
	m_position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterKoopa::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}