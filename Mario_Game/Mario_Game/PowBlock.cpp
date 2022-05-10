#include <iostream>
#include "PowBlock.h"
#include "Texture2D.h"
#include "Commons.h"
#include "constants.h"
#include "LevelMap.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D position)
{
	//Find powblock texture from file
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile("Images/PowBlock.png"))
	{
		cout << "Failed to load powBlock texture" << endl;
		return;
	}

	m_level_map = map;

	//Get powblock width and height
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_num_hits_left = 3;
	//Set positon of the powblock in the level
	m_position = position;
}

PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	m_level_map = nullptr;

	//Call Texture2D deconstructor
	delete m_texture;
	m_texture = nullptr;
}

void PowBlock::Render(SDL_Rect camera_rect)
{
	//Render part of the powblock according to the number of hits left
	if (m_num_hits_left > 0)
	{
		int left = m_single_sprite_w * (m_num_hits_left - 1);
		SDL_Rect portion_of_sprite = { left,0, m_single_sprite_w, m_single_sprite_h };
		SDL_Rect dest_rect = { static_cast<int>(m_position.x - camera_rect.x), static_cast<int>(m_position.y - camera_rect.y), m_single_sprite_w, m_single_sprite_h };

		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeHit(int w, int h)
{
	//Reduce the number of hit left
	m_num_hits_left--;
	if (m_num_hits_left <= 0)
	{
		//Change specific tile from 1 to 0 when powblock is gone
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(w, h, 0);
	}
}