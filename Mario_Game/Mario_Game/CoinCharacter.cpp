#include "CoinCharacter.h"

CoinCharacter::CoinCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	//set veriables
	m_current_frame = 0;
	m_frame_delay = 0;
	m_animation_frames = frames;

	//Get Coin sprites dimensions
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CoinCharacter::~CoinCharacter() {}

void CoinCharacter::Render(SDL_Rect camera_rect)
{
	//Render Coin and not follow camera
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w,m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x - camera_rect.x), (int)(m_position.y - camera_rect.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);

}

void CoinCharacter::Update(float deltaTime, SDL_Event e)
{
	//Call Coin Animation
	DefaultAnimation(deltaTime);
}

void CoinCharacter::DefaultAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//reset frame dlay count
		m_frame_delay = ANIMATION_DELAY;

		//change frame
		m_current_frame++;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
			m_current_frame = 0;
	}
}
