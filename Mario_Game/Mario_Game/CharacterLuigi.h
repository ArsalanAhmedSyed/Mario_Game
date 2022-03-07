#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"
#include "Commons.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

	void AddGravity(float deltaTime) override;
	void Jump() override;

private:
};

#endif // !_CHARACTERLUIGI_H

