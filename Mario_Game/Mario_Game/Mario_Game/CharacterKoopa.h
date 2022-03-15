#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include "LevelMap.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	bool GetInjured() { return m_injured; }

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;



private:
	void FlipRightwayUp();

	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_injured_time;
	bool m_injured;
};

#endif // _CHARACTERKOOPA_H

