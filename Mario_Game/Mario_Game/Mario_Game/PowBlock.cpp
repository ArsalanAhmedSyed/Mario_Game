#include <iostream>
#include "PowBlock.h"
#include "Texture2D.h"
#include "Commons.h"
#include "constants.h"
#include "LevelMap.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load powBlock texture" << endl;
		return;
	}

	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5, 260);
}

PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	m_level_map = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		int left = m_single_sprite_w * (m_num_hits_left - 1);
		SDL_Rect portion_of_sprite = { left,0, m_single_sprite_w, m_single_sprite_h };
		SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };

		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeHit()
{
	m_num_hits_left--;
	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
		m_level_map->ChangeTileAt(7, 8, 0);
	}
}