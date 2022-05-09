#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	//Pass the parameter values
	m_facing_direction = start_facing;
	m_position = start_position;
	m_animation_frames = frames;

	//Set default values
	m_injured = false;
	m_turn_anim = false;
	m_roll_anim = false;
	
	//Get Sprites width and height
	m_single_sprite_w = m_texture->GetWidth() / m_animation_frames;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa() {}

void CharacterKoopa::Render(SDL_Rect camera_rect)
{
	//set SDL_Rect
	SDL_Rect m_source = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect m_draw_rect = { (int)m_position.x - camera_rect.x, (int)m_position.y - camera_rect.y, m_texture->GetWidth() / m_animation_frames,m_texture->GetHeight() };

	//Render Texture according to the character facing direction
	if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(m_source, m_draw_rect, SDL_FLIP_HORIZONTAL);
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_source, m_draw_rect, SDL_FLIP_NONE);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	CharacterCondition(deltaTime);
	PlatformHit(deltaTime, RightX_position, LeftX_position, centralY_position);
	KeepOnScreen(deltaTime);

	Character::Update(deltaTime, e);
}

void CharacterKoopa::TakeDamage()
{
	//Change to injured sprite
	m_current_frame = 9;

	//Setup injured veriables
	m_injured = true;
	m_injured_time = INJURED_TIME;
	m_jump_force = INIITAL_JUMP_FORCE_SMALL;
	
	Jump();
}

void CharacterKoopa::CharacterCondition(float deltaTime)
{
	if (!m_injured)
	{
		if (!m_turn_anim && !m_roll_anim)
		{
			//Default walk animation
			DefaultAnimation(deltaTime);

			//Move towards the direction koopa is facing
			if (m_facing_direction == FACING_LEFT)
			{
				MoveLeft(deltaTime);
			}
			else if (m_facing_direction == FACING_RIGHT)
			{
				MoveRight(deltaTime);
			}
		}

		//Play turn Animation on turn
		if (m_turn_anim)
		{
			TurnAnimation(deltaTime);
		}

		//Play roll over Annimation 
		if (m_roll_anim)
		{
			RollOverAnimation(deltaTime);
		}
	}
	else
	{
		//Deny movement when injured
		m_moving_right = false;
		m_moving_left = false;

		//Start injured timer to make injured false
		m_injured_time -= deltaTime;
		if (m_injured_time <= 0.0f)
		{
			m_injured = false;
			m_roll_anim = true;
		}
	}

}

void CharacterKoopa::PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y)
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
		m_turn_anim = true;
		m_current_frame = 6;

		ChangeDirection();
	}

	//Check if there are tiles on the Left side of the character
	if (m_current_level_map->GetTileAt(centralY_position, LeftX_position) == 1)
	{
		m_position.x += deltaTime * ENEMY_SPEED;
		m_turn_anim = true;
		m_current_frame = 6;

		ChangeDirection();
	}
}

void CharacterKoopa::DefaultAnimation(float deltaTime)
{
	//Perform walking animation
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = KOOPA_ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 4)
			m_current_frame = 0;
	}
}

void CharacterKoopa::TurnAnimation(float deltaTime)
{
	//Perform Turning rotaion
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = KOOPA_ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 8)
		{
			m_current_frame = 0;
			m_turn_anim = false;

			ChangeDirection();
		}
	}
}

void CharacterKoopa::RollOverAnimation(float deltaTime)
{
	//Perform roll over animation
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = KOOPA_ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 14)
		{
			m_current_frame = 0;
			m_roll_anim = false;
		}
	}
}

void CharacterKoopa::KeepOnScreen(float deltaTime)
{
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > LEVEL_WIDTH)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_position.x -= deltaTime * ENEMY_SPEED;
	}
	else if (m_position.x < 0)
	{
		m_turn_anim = true;
		m_current_frame = 6;
		m_position.x += deltaTime * ENEMY_SPEED;
	}
}

void CharacterKoopa::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * ENEMY_SPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterKoopa::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * ENEMY_SPEED;
	m_facing_direction = FACING_LEFT;
}

void CharacterKoopa::ChangeDirection()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
}
