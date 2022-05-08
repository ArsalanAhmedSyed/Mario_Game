#include "Character.h"
#include "LevelMap.h"
#include "CharacterMario.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames)
{
	//Parameter
	m_renderer = renderer;
	m_position = start_position;
	m_current_level_map = map;
	m_animation_frames = frames;

	//Movement
	m_moving_left = false;
	m_moving_right = false;

	//Check Alive condition
	m_alive = true;
	m_kill_player = false;
	m_kill_timer = 1.6f;

	//sprite Animation set
	m_current_frame = 0;
	m_frame_delay = 0.0f;
	m_animation_frames = frames;
	m_jump_Anim = false;

	m_collision_radius = 15.0f;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_sound = new SoundEffect();
	m_play_jump_audio = false;	
}

Character::~Character()
{
	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Character::SetPosition(Vector2D new_position) { m_position = new_position; }

Vector2D Character::getPosition() { return m_position; }

void Character::Render(SDL_Rect rect) 
{

	m_source = { 0,0,m_texture->GetWidth(),m_texture->GetHeight() };
	m_draw_rect = { (int)m_position.x - rect.x, (int)m_position.y - rect.y, m_texture->GetWidth(),m_texture->GetHeight() };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_source, m_draw_rect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_source, m_draw_rect, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_jumping)
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}	
	}

	//collision position variables
	centralX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames * 0.5)) / TILE_WIDTH;
	centralY_position = (int)(m_position.y + m_texture->GetHeight() * 0.5) / TILE_HEIGHT;

	foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	head_position = (int)(m_position.y + m_texture->GetHeight() * 0.2) / TILE_HEIGHT;

	RightX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames)) / TILE_WIDTH;
	LeftX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames* 0.2)) / TILE_WIDTH;


	//foot check
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		// deal with gravity
		AddGravity(deltaTime);
		m_jump_Anim = true;
		m_play_jump_audio = false;
	}
	else
	{
		//collided with ground so can jump again
		m_can_jump = true;
		m_jump_Anim = false;		
	}

	//head check
	if (m_current_level_map->GetTileAt(head_position, centralX_position) == 1)
	{
		m_jumping = false;
	}

	PlatformHit(deltaTime, RightX_position,LeftX_position, centralY_position);
	KeepOnScreen(deltaTime);
}

void Character::AddGravity(float deltaTime) 
{
	m_position.y += GRAVITY * deltaTime;
}

void Character::Jump() 
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
		m_play_jump_audio = true;
	}
}

void Character::KeepOnScreen(float deltaTime)
{
	if (m_position.x + m_texture->GetWidth() / m_animation_frames > LEVEL_WIDTH)
	{
		m_facing_direction = FACING_LEFT;
		m_position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_position.x < 0)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x += deltaTime * MOVEMENT_SPEED;
	}
}

void Character::MoveLeft(float deltaTime) {}

void Character::MoveRight(float deltaTime) {}

void Character::RunAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 3)
			m_current_frame = 1;
	}
}

void Character::PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y)
{
	//side check
	if (m_current_level_map->GetTileAt(centralY_position, RightX_position) == 1)
	{
		m_position.x -= deltaTime * MOVEMENT_SPEED;

		if (m_facing_direction == FACING_RIGHT)
		{
			m_facing_direction = FACING_LEFT;
		}
	}

	if (m_current_level_map->GetTileAt(centralY_position, LeftX_position) == 1)
	{
		m_position.x += deltaTime * MOVEMENT_SPEED;

		if (m_facing_direction == FACING_LEFT)
		{
			m_facing_direction = FACING_RIGHT;
		}
	}
	
}