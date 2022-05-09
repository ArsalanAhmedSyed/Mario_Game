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

	m_facing_direction = FACING_LEFT;
	m_collision_radius = 15.0f;

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

	//Get Character sprite location
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}

	//Initialize sound effect class
	m_sound = new SoundEffect();
	m_play_jump_audio = false;	

	m_single_sprite_w = m_texture->GetWidth() / frames;
	m_single_sprite_h = m_texture->GetHeight();

	m_grounded = false;
}

Character::~Character()
{
	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Character::Render(SDL_Rect camrea_rect) 
{
	//set SDL_Rect
	SDL_Rect m_source = {m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect m_draw_rect = { (int)m_position.x - camrea_rect.x, (int)m_position.y - camrea_rect.y, m_texture->GetWidth() / m_animation_frames,m_texture->GetHeight() };

	//Render Texture according to the character facing direction
	if (m_facing_direction == FACING_LEFT)
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
		//slowly reduce jump force
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			if(m_grounded)
				m_jumping = false;
		}	
	}

	CharacterCondition(deltaTime);

	CharacterDimension();

	if(!m_kill_player)
		PlatformHit(deltaTime, RightX_position,LeftX_position, centralY_position);

	if (m_kill_player)
		AddGravity(deltaTime);

	KeepOnScreen(deltaTime);
}

void Character::AddGravity(float deltaTime) 
{
	//Add gravity to bring down the character
	m_position.y += GRAVITY * deltaTime;
}

void Character::Jump() 
{
	//Setup veriables to allow the character to jump
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
	//Keep character on screen
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

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_RIGHT;
}


void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::DefaultAnimation(float deltaTime)
{
	//CReate Running animation
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 3)
			m_current_frame = 1;
	}
}

void Character::CharacterDimension()
{
	//Character Central positons
	centralX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames * 0.5)) / TILE_WIDTH;
	centralY_position = (int)(m_position.y + m_texture->GetHeight() * 0.5) / TILE_HEIGHT;

	//Character Vertical positions
	foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	head_position = (int)(m_position.y + m_texture->GetHeight() * 0.2) / TILE_HEIGHT;

	//Character Horizontal positions
	RightX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames)) / TILE_WIDTH;
	LeftX_position = (int)(m_position.x + (m_texture->GetWidth() / m_animation_frames * 0.2)) / TILE_WIDTH;
}

void Character::CharacterCondition(float deltaTime)
{
	if (m_moving_left && !m_kill_player)
	{
		MoveLeft(deltaTime);

		if (!m_jump_Anim)
			DefaultAnimation(deltaTime);
	}
	else if (m_moving_right && !m_kill_player)
	{
		MoveRight(deltaTime);

		if (!m_jump_Anim)
			DefaultAnimation(deltaTime);
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
}

void Character::PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y)
{
	//foot check
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		//deal with gravity
		AddGravity(deltaTime);
		m_jump_Anim = true;
		m_play_jump_audio = false;
		m_grounded = false;
	}
	else
	{
		//Allow player to jump once collided with ground
		m_can_jump = true;
		m_jump_Anim = false;
		m_grounded = true;
	}

	//head check
	if (m_current_level_map->GetTileAt(head_position, centralX_position) == 1)
	{
		//stop the character from jumping further
		m_jumping = false;
	}

	//Check if there are tiles on the right side of the character
	if (m_current_level_map->GetTileAt(centralY_position, RightX_position) == 1)
	{
		m_position.x -= deltaTime * MOVEMENT_SPEED;

		if (m_facing_direction == FACING_RIGHT)
		{
			m_facing_direction = FACING_RIGHT;
		}
	}

	//Check if there are tiles on the Left side of the character
	if (m_current_level_map->GetTileAt(centralY_position, LeftX_position) == 1)
	{
		m_position.x += deltaTime * MOVEMENT_SPEED;

		if (m_facing_direction == FACING_LEFT)
		{
			m_facing_direction = FACING_LEFT;
		}
	}
	
}