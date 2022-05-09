#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, int frames);
	~CharacterKoopa();

	void Update(float deltaTime, SDL_Event e) override;
	void Render(SDL_Rect camrea_rect);
	
	//Damage relate functions
	void TakeDamage();
	bool GetInjured() { return m_injured; }

	//Movement functions
	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

private:
	//Animations
	void TurnAnimation(float deltaTime);
	void RollOverAnimation(float deltaTime);
	void DefaultAnimation(float deltaTime) override;
	bool m_turn_anim;
	bool m_roll_anim;

	void KeepOnScreen(float deltaTime) override;
	void CharacterCondition(float deltaTime) override;
	void PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y);

	void ChangeDirection();

	float m_injured_time;
	bool m_injured;
};

#endif // _CHARACTERKOOPA_H

