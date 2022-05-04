#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H

#include "Character.h"

class CharacterGoomba : public Character
{
public:

	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed, int frames);
	~CharacterGoomba();

	void Render(SDL_Rect camera_rect);
	void Update(float deltaTime, SDL_Event e);

private:
	void RunAnimation(float deltaTime) override;
	void KeepOnScreen(float deltaTime) override;

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;
};

#endif // !_CHARACTERGOOMBA_H
