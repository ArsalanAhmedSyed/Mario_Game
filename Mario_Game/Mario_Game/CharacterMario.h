#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "Commons.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~CharacterMario();

	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;

protected:
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	void RunAnimation(float deltaTime);

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_current_frame;
	float m_frame_delay;
};

#endif //_CHARACTERMARIO_H

