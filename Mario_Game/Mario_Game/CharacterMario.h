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

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;
	void PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y) override;

protected:
	void Update(float deltaTime, SDL_Event e) override;
	void Render(SDL_Rect camera_rect) override;
	void KeepOnScreen(float deltaTime) override;
private:
};

#endif //_CHARACTERMARIO_H

