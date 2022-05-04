#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"
#include "Commons.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~CharacterLuigi();

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

protected:
	void Update(float deltaTime, SDL_Event e) override;
	void Render(SDL_Rect camera_rect) override;

private:

};

#endif // !_CHARACTERLUIGI_H

