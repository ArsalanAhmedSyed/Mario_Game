#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H

#include "Character.h"

class CharacterGoomba : public Character
{
public:

	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, int frames);
	~CharacterGoomba();

	void Render(SDL_Rect camera_rect);
	void Update(float deltaTime, SDL_Event e);

private:
	//Animation
	void DefaultAnimation(float deltaTime) override;
	//Keep Character in side the level width
	void KeepOnScreen(float deltaTime) override;
	//Check Goomba Walking
	void CharacterCondition(float deltaTime);
	//Check Goomba Platform hit condition
	void PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y);

	//Movement 
	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;
};

#endif // !_CHARACTERGOOMBA_H
