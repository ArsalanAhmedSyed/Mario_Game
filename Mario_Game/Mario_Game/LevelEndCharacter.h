#ifndef _LEVELENDCHARACTER_H
#define _LEVELENDCHARACTER_H

#include "Character.h"
class LevelEndCharacter : public Character
{
public:
	LevelEndCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~LevelEndCharacter();

	void Render(SDL_Rect camera_rect) override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	//void Animation(float deltaTime);
};

#endif // !_LEVELENDCHARACTER_H



