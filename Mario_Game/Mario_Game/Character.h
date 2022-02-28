#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Commons.h"
#include "Texture2D.h"
#include <SDL.h>
#include <iostream>
using namespace std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	Vector2D getPosition();

	float GetCollisionRaidus();

	Rect2D getCollisionBox() { return Rect2D(m_Position.x, m_Position.y, m_Texture->GetWidth(), m_Texture->GetHeight()); }

protected:
	SDL_Renderer* m_Renderer;
	Vector2D m_Position;
	Texture2D* m_Texture;

	bool m_moving_left;
	bool m_moving_right;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	virtual void AddGravity(float deltaTime);
	virtual void Jump();

	bool m_can_jump;
	bool m_jumping;
	float m_jump_force;

	float m_collision_radius;

private:
	FACING m_facing_direction;
};

#endif // !_CHARACTER_H



