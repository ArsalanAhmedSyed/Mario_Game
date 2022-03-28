#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constants.h"
#include "Texture2D.h"

using namespace std;

class Texture2D;
class LevelMap;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }

	Vector2D getPosition();
	Circle2D GetCollisionCircle() { return Circle2D(m_Position.x, m_Position.y, m_collision_radius); }
	Rect2D getCollisionBox() { return Rect2D(m_Position.x, m_Position.y, m_Texture->GetWidth()/ m_animation_frames, m_Texture->GetHeight()); }

	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }



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

	//keep everything in screen
	virtual void KeepOnScreen(float deltaTime);

	bool m_can_jump;
	bool m_jumping;
	float m_jump_force;
	float m_movement_speed;
	float m_collision_radius;

	FACING m_facing_direction;
	int m_animation_frames;

	bool m_alive;
	bool m_jump_Anim;

	//Spirte animation
	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_current_frame;
	float m_frame_delay;

	virtual void RunAnimation(float deltaTime);

private:
	LevelMap* m_current_level_map;
};

#endif // !_CHARACTER_H



