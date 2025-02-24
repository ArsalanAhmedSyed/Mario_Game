#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include <SDL.h>
#include "Commons.h"

class LevelMap;
class Texture2D;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D position);
	~PowBlock();

	void Render(SDL_Rect camera_rect);

	void TakeHit(int w, int h);
	//Return the number of hits left
	bool IsAvailable() { return m_num_hits_left > 0; }

	//Get box collision for the powblock
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h); }
	
private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
};

#endif // !_POWBLOCK_H


