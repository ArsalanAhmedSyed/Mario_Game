#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"
#include "Commons.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e) override;
};

#endif // !_CHARACTERLUIGI_H

