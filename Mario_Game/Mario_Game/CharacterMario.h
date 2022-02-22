#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
class CharacterMario : Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


};

#endif _CHARACTERMARIO_H

