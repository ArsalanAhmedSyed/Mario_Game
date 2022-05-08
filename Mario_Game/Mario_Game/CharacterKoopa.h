#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames);
	~CharacterKoopa();

	void Render(SDL_Rect rect) override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	bool GetInjured() { return m_injured; }

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

private:
	//void FlipRightwayUp(float deltaTime);
	void TurnAnimation(float deltaTime);
	void RollOverAnimation(float deltaTime);

	void RunAnimation(float deltaTime) override;
	void KeepOnScreen(float deltaTime) override;

	//void Jump() override;

	float m_injured_time;
	bool m_injured;

	bool m_turn_anim;
	bool m_roll_anim;
};

#endif // _CHARACTERKOOPA_H

