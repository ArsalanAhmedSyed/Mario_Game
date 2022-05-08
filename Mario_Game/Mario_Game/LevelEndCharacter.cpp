#include "LevelEndCharacter.h"


LevelEndCharacter::LevelEndCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames) : Character(renderer, imagePath, start_position, map, frames)
{
	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight() / 2;

	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load Peech Sprite!" << endl;
	}
}

LevelEndCharacter::~LevelEndCharacter() {}

void LevelEndCharacter::Render(SDL_Rect camera_rect)
{
	SDL_Rect portion_of_sprite = { 0,0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect desRect = { (int)(m_position.x - camera_rect.x), (int)(m_position.y - camera_rect.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, desRect, SDL_FLIP_HORIZONTAL);
}

void LevelEndCharacter::Update(float deltaTime, SDL_Event e)
{
	//Animation(deltaTime);
}

//void LevelEndCharacter::Animation(float deltaTime)
//{
//	m_frame_delay -= deltaTime;
//	if (m_frame_delay <= 0.0f)
//	{
//		m_frame_delay = ANIMATION_DELAY;
//
//		m_current_frame++;
//
//		if (m_current_frame > 1)
//			m_current_frame = 0;
//	}
//}