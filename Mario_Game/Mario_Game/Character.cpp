#include "Character.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames)
{
	//Parameter
	m_Renderer = renderer;
	m_Position = start_position;
	m_current_level_map = map;
	m_animation_frames = frames;

	//Movement
	m_moving_left = false;
	m_moving_right = false;

	//Check Alive condition
	m_alive = true;
	m_kill_player = false;
	m_kill_timer = 1.0f;

	//sprite Animation set
	m_current_frame = 0;
	m_frame_delay = 0.0f;
	m_animation_frames = frames;
	m_jump_Anim = false;

	m_collision_radius = 15.0f;

	m_Texture = new Texture2D(m_Renderer);
	if (!m_Texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	m_sound = new SoundEffect();
	m_play_jump_audio = false;
}

Character::~Character()
{
	m_Renderer = nullptr;

	delete m_Texture;
	m_Texture = nullptr;
}

void Character::SetPosition(Vector2D new_position) { m_Position = new_position; }

Vector2D Character::getPosition() { return m_Position; }

void Character::Render() 
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_Texture->Render(m_Position, SDL_FLIP_NONE);
	}
	else
	{
		m_Texture->Render(m_Position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_jumping)
	{
		m_Position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}	
	}

	//collision position variables
	int centralX_position = (int)(m_Position.x + (m_Texture->GetWidth() / m_animation_frames * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_Position.y + m_Texture->GetHeight()) / TILE_HEIGHT;

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

	KeepOnScreen(deltaTime);
}

void Character::AddGravity(float deltaTime) 
{
	m_Position.y += GRAVITY * deltaTime;
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
	if (m_Position.x + m_Texture->GetWidth() / m_animation_frames > SCREEN_WIDTH)
	{
		m_facing_direction = FACING_LEFT;
		m_Position.x -= deltaTime * MOVEMENT_SPEED;
	}
	else if (m_Position.x < 0)
	{
		m_facing_direction = FACING_RIGHT;
		m_Position.x += deltaTime * MOVEMENT_SPEED;
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