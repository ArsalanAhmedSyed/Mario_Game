#ifndef _COINCHARACTER_H
#define _COINCHARACTER_H

#include "Character.h"

class CoinCharacter : public Character
{
public:
	CoinCharacter(SDL_Renderer* renderer, string imagePath,Vector2D start_position, LevelMap* map, int frames);
	~CoinCharacter();

	void Render(SDL_Rect camera_rect) override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	int m_current_frame;
};

#endif // !_COINCHARACTER_H