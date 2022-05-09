#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing,int frames) : Character(renderer, imagePath,start_position,map,frames)
{
	//Pass values from parameter
	m_facing_direction = start_facing;
	m_position = start_position;
	m_animation_frames = frames;

	//Get Width and height of the sprite
	m_single_sprite_w = m_texture->GetWidth() / m_animation_frames ;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterGoomba::~CharacterGoomba() {}

void CharacterGoomba::Render(SDL_Rect camera_rect)
{
	if (m_alive)
	{
		//Render Goomba and not follow the camera
		SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };
		SDL_Rect destRect = { (int)(m_position.x - camera_rect.x), (int)(m_position.y - camera_rect.y), m_single_sprite_w, m_single_sprite_h };

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
	CharacterCondition(deltaTime);
	PlatformHit(deltaTime, RightX_position, LeftX_position, centralY_position);
	KeepOnScreen(deltaTime);

	Character::Update(deltaTime, e);
}

void CharacterGoomba::DefaultAnimation(float deltaTime)
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
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > LEVEL_WIDTH)
	{
		m_facing_direction = FACING_LEFT;
	}
	else if (m_position.x < 0)
	{
		m_facing_direction = FACING_RIGHT;
	}
}

void CharacterGoomba::CharacterCondition(float deltaTime)
{
	//Play the animation
	DefaultAnimation(deltaTime);

	//Move in the direction of Goomba facing
	if (m_facing_direction == FACING_LEFT)
	{
		MoveLeft(deltaTime);
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		MoveRight(deltaTime);
	}
}

void CharacterGoomba::PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y)
{
	//foot check
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		//deal with gravity
		AddGravity(deltaTime);
	}

	//Check if there are tiles on the right side of the character
	if (m_current_level_map->GetTileAt(centralY_position, RightX_position) == 1)
	{
		m_position.x -= deltaTime * ENEMY_SPEED;

		if (m_facing_direction == FACING_RIGHT)
			m_facing_direction = FACING_LEFT;
	}

	//Check if there are tiles on the Left side of the character
	if (m_current_level_map->GetTileAt(centralY_position, LeftX_position) == 1)
	{
		m_position.x += deltaTime * ENEMY_SPEED;

		if (m_facing_direction == FACING_LEFT)
			m_facing_direction = FACING_RIGHT;
	}
}

void CharacterGoomba::MoveRight(float deltaTime)
{
	//Move to the right and face right
	m_position.x += deltaTime * ENEMY_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterGoomba::MoveLeft(float deltaTime)
{
	//Move to the left and face left
	m_position.x -= deltaTime * ENEMY_SPEED;
	m_facing_direction = FACING_LEFT;
}
