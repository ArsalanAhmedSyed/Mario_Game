#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include "LevelMap.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames);
	~CharacterKoopa();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	bool GetInjured() { return m_injured; }

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;



private:
	void FlipRightwayUp();
	void TurnAnimation(float deltaTime);

	void RunAnimation(float deltaTime) override;
	void KeepOnScreen(float deltaTime) override;

	float m_injured_time;
	bool m_injured;

	bool turn;
};

#endif // _CHARACTERKOOPA_H

