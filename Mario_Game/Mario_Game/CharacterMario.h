#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "Commons.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

	void AddGravity(float deltaTime) override;
	void Jump() override;

private:

};

#endif //_CHARACTERMARIO_H

