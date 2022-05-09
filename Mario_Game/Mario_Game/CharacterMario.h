#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "Commons.h"

class SoundEffect;

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e) override;
};

#endif //_CHARACTERMARIO_H

