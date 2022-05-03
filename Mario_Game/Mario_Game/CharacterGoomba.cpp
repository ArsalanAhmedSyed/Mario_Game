#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames) : Character(renderer, imagePath,start_position,map,frames)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_animation_frames = frames;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load Goomba texture!" << endl;
	}

	m_single_sprite_w = m_texture->GetWidth() / m_animation_frames ;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterGoomba::~CharacterGoomba() {}

void CharacterGoomba::Render()
{
	if (m_alive)
	{
		SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };
		SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

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

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
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

	KeepOnScreen(deltaTime);
	Character::Update(deltaTime, e);
}

void CharacterGoomba::RunAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame >= m_animation_frames)
			m_current_frame = 0;
	}
}

void CharacterGoomba::KeepOnScreen(float deltaTime)
{
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > SCREEN_WIDTH)
	{
		m_facing_direction = FACING_LEFT;
	}
	else if (m_position.x < 0)
	{
		m_facing_direction = FACING_RIGHT;
	}
}

void CharacterGoomba::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterGoomba::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}
